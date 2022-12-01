#include "observer_internals.hpp"

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "ext/ranges.hpp"

#include "javascript/environment/realms.hpp"
#include "javascript/environment/global_slots.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)

#include "dom/detail/event_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/mutations/mutation_observer.hpp"
#include "dom/mutations/mutation_observer_private.hpp"
#include "dom/mutations/mutation_record.hpp"
#include "dom/mutations/mutation_record_private.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"
#include "dom/other/dom_implementation.hpp"
#include "dom/other/dom_implementation_private.hpp"

#include "html/elements/html_slot_element.hpp"
#include "html/elements/html_slot_element_private.hpp"

#include <magic_enum.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/map.hpp>
#include <v8-function-callback.h>


auto dom::detail::notify_mutation_observers() -> void
{
    auto e = js::env::env::surrounding(nullptr);
    using notify_set_t = ext::set<mutations::mutation_observer*>;
    using signal_set_t = ext::set<html::elements::html_slot_element*>;

    // TODO : move to dom::nodes::window (Why? - made TODO comment long time ago)
    // Set the 'mutation_observer_microtask_queued' variable to false, and get the 'notify_set' (MutationObserver set),
    // and the signal set (HTMLSlotElement set). clear the 'signal_set' in the environment (clone is saved locally).
    js::env::set_slot(e, js::global_slots::mutation_observer_microtask_queued, ext::boolean::FALSE_());
    decltype(auto) notify_set = js::env::get_slot<notify_set_t*>(e, js::global_slots::notify_observers);
    decltype(auto) signal_set = js::env::get_slot<signal_set_t*>(e, js::global_slots::signal_slots);
    js::env::set_slot(e, js::global_slots::signal_slots, ext::nullptr_cast<signal_set_t*>());

    // Iterate every MutationObserver in the 'notify_set'.
    for (decltype(auto) mo: *notify_set)
    {
        // Empty the record queue in each MutationObserver, by swapping the list held in the pointer with an empty list;
        // the queue of records is now stored locally.
        auto records = ext::queue<mutations::mutation_record*>{};
        mo->d_func()->record_queue.swap(records);

        // Iterate each node in the MutationObserver's node list, and for each transient registered observer (a
        // registered observer who has a source) linked to the node, remove it if its observer is 'mo' - this means that
        // any observers whose 'observer' link is 'mo', and who belong to a node that is tied to 'mo' are removed.
        // TODO : why?
        for (decltype(auto) node: *mo->d_func()->node_list)
            node->d_func()->registered_observer_list = node->d_func()->registered_observer_list
                    | ranges::views::cast<transient_registered_observer_t*>
                    | ranges::views::remove_if([mo](auto* observer) {return observer->observer.get() == mo;});

        // if there are any MutationRecords from the JavaScript environment, call 'mo''s callback with the list of
        // records, reporting any exceptions that are caught during the process.
        if (!records.empty())
        {
            JS_EXCEPTION_HANDLER;
            mo->d_func()->callback(records, mo);

            if (JS_EXCEPTION_HAS_THROWN)
                console::reporting::report_exception(JS_EXCEPTION_MESSAGE)
        }
    }

    // Fire a "slotchange" event at every slot in the JavaScript environment list. TODO : why
    for (decltype(auto) slot: *signal_set)
        fire_event(u"slotchange", slot, {{u"bubbles", true}});
}


template <typename F>
auto dom::detail::queue_microtask(F&& steps, v8::Isolate* event_loop, nodes::document* document) -> void
{
    JS_BLOCK_ENTER
        auto e = js::env::env::implied();

        // Set the 'event loop' and 'document' to the implied objects (via the implied realm). TODO
        event_loop = event_loop ? event_loop : e.js.agent();
        document = document ? document : implied_document();

        // Create a microtask and assign it the relevant data. TODO
        const v8::Local<v8::Function> microtask = v8::Function::New(event_loop->GetCurrentContext(), std::forward<F>(steps));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "source"), microtask->TaskSource());
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "document"), v8pp::to_v8(event_loop, document));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "set"), v8pp::to_v8(event_loop, ext::set<void*>{}));

        // Enqueue the microtask to the event loop.
        event_loop->EnqueueMicrotask(microtask);
    JS_BLOCK_EXIT
}


auto dom::detail::queue_mutation_record(
        dom::detail::mutation_type_t type,
        nodes::node* target,
        ext::string_view name,
        ext::string_view namespace_,
        ext::string_view old_value,
        ext::vector_span<nodes::node*> added_nodes,
        ext::vector_span<nodes::node*> removed_nodes,
        nodes::node* previous_sibling,
        nodes::node* next_sibling)
        -> void
{
    using enum mutation_type_t;

    // Created a map of MutationObservers to strings, to save observers of interest, and get all the ancestors of the
    // target node, as these nodes' registered observer lists contains the MutationObserver objects that may be of
    // interest.
    auto interested_observers = ext::map<mutations::mutation_observer*, ext::string>{};
    auto nodes = ancestors(target);

    // Iterate each MutationObserver for each node.
    for (decltype(auto) node: nodes)
    {
        for (registered_observer_t* registered: node->d_func()->registered_observer_list | ranges::views::transform(&std::unique_ptr<registered_observer_t>::get))
        {
            // If the conditions based on the 'type' and 'options' dictionary are valid, then modify the
            // 'interested_observers' map. Copy this map so 'try_emplace(...)' doesn't change anything.
            auto options = registered->options;

            if (type == ATTRIBUTES && options.try_emplace(u"attributes").second && (ranges::contains(options[u8"attributeFilter"].to<ext::vector<ext::string>>(), name) || !namespace_.empty())
                || node != target && options[u"subtree", true].to<ext::boolean>() == false
                || type == CHILD_LIST && options[u"childList", true].to<ext::boolean>() == false
                || type == ATTRIBUTES && options[u"attributes", true].to<ext::boolean>() == false
                || type == CHARACTER_DATA && options[u"characterData", true].to<ext::boolean>() == false)
            {
                decltype(auto) mo = registered->observer.get();

                // If the MutationObserver is not in the map, then insert it with an empty string as the corresponding
                // value.
                if (!ranges::contains(interested_observers | ranges::views::keys, mo))
                    interested_observers.insert_or_assign(mo, u"");

                // If there is a valid old value supplied in the 'options' dictionary that matches the 'type', then set
                // the value of the MutationObserver to the old value.
                if (type == ATTRIBUTES && options.try_emplace(u"attributeOldValue", false).first->second == true
                        || type == CHARACTER_DATA && options.try_emplace(u"characterDataOldValue", false).first->second == true)
                    interested_observers.insert_or_assign(mo, old_value);
            }
        }
    }

    // Iterate over each interested observer, and emplace a mutation record into the observer based on the parameters
    // and the 'mapped_old_value' string.
    for (const auto& [observer, mapped_old_value]: interested_observers)
    {
        auto record = std::make_unique<mutations::mutation_record>();
        record->d_func()->type = magic_enum::enum_name(type) | ranges::views::lowercase | ranges::to<ext::string>;
        record->d_func()->attribute_name = name;
        record->d_func()->attribute_namespace = namespace_;
        record->d_func()->old_value = mapped_old_value;
        record->d_func()->target = target;
        record->d_func()->previous_sibling = previous_sibling;
        record->d_func()->next_sibling = next_sibling;
        record->d_func()->added_nodes.assign(added_nodes.begin(), added_nodes.end());
        record->d_func()->removed_nodes.assign(removed_nodes.begin(), removed_nodes.end());
        observer->d_func()->record_queue.push(std::move(record));
    }

    // Queue a mutation observers microtask
    queue_mutation_observer_microtask();
}


auto dom::detail::queue_tree_mutation_record(
        nodes::node* const target,
        ext::vector_span<nodes::node*> added_nodes,
        ext::vector_span<nodes::node*> removed_nodes,
        nodes::node* const previous_sibling,
        nodes::node* const next_sibling)
        -> void
{
    using enum mutation_type_t;

    // There has to be an element in either the 'added_nodes' or 'removed_nodes' list, as otherwise there is no mutation
    // happening; this method is just a wrapper around 'queue_mutation_record', so call that method with some parameters
    // set to fixed values.
    assert(!added_nodes.empty() || !removed_nodes.empty());
    queue_mutation_record(CHILD_LIST, target, u"", u"", u"", added_nodes, removed_nodes, previous_sibling, next_sibling);
}


auto dom::detail::queue_mutation_observer_microtask() -> void
{
    auto e = js::env::env::surrounding(nullptr);

    // Get if the surrounding global object's 'mutation_observer_microtask_queued' attribute is set to true; return
    // early if it is, otherwise set it to true, and queue a microtask to 'notify_mutation_observers()'.
    return_if(js::env::get_slot<ext::boolean>(e, js::global_slots::mutation_observer_microtask_queued));
    js::env::set_slot(e, js::global_slots::mutation_observer_microtask_queued, ext::boolean::TRUE_());

    queue_microtask(&notify_mutation_observers);
}


template <typename F>
auto dom::detail::queue_task(
        html::detail::task_queue_t& task_source,
        F&& steps,
        v8::Isolate* event_loop,
        nodes::document* document)
        -> void
{
    JS_BLOCK_ENTER
        // TODO : fix, JS block? and comment
        auto e = js::env::env::implied();
        event_loop = event_loop ? event_loop : e.js.agent();
        document = document ? document : implied_document();

        const v8::Local<v8::Function> microtask = v8::Function::New(event_loop->GetCurrentContext(), std::forward<F>(steps));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "source"), task_source);
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "document"), v8pp::to_v8(event_loop, document));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "set"), v8pp::to_v8(event_loop, ext::set<void*>{}));

        // Enqueue the microtask to the event loop
        event_loop->EnqueueMicrotask(microtask);
    JS_BLOCK_EXIT
}


template <typename F>
auto dom::detail::queue_global_task(
        html::detail::task_queue_t& task_source,
        const v8::Local<v8::Object> global_object,
        F&& steps)
        -> void
{
    auto e = js::env::env::relevant(global_object);
    decltype(auto) document = e.cpp.template global<dom::nodes::window*>()
            ? e.cpp.template global<dom::nodes::window*>()->d_func()->document.get()
            : nullptr;

    queue_task(task_source, std::forward<F>(steps), e.js.agent(), document);
}


template <typename F>
auto dom::detail::queue_element_task(
        html::detail::task_queue_t& task_source,
        const html::elements::html_element* const element,
        F&& steps)
        -> void
{
    auto e = js::env::env::relevant(element);
    queue_global_task(task_source, e.js.global(), std::forward<F>(steps));
}
