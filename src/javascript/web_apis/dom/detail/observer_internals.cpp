#include "observer_internals.hpp"

#include "ext/optional.hpp"
#include "ext/ranges.hpp"
#include "html/_typedefs.hpp"
#include "javascript/environment/realms_2.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/mutations/mutation_observer.hpp"
#include "dom/mutations/mutation_record.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_implementation.hpp"

#include <magic_enum.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/map.hpp>
#include <v8-function-callback.h>

namespace html::elements {class html_slot_element;}


auto dom::detail::notify_mutation_observers() -> void
{
    // set the 'mutation_observer_microtask_queued' variable to false, and get the 'notify_set' (MutationObserver set),
    // and the signal set (HTMLSlotElement set). clear the 'signal_set' in the environment (clone is saved locally)

    JS_REALM_GET_SURROUNDING(nullptr)
    using notify_set_t = ext::set<mutations::mutation_observer*>;
    using signal_set_t = ext::set<html::elements::html_slot_element*>;

    javascript::environment::realms_2::set(nullptr_surrounding_global_object, "mutation_observer_microtask_queued", false);
    const auto notify_set = javascript::environment::realms_2::get<notify_set_t>(nullptr_surrounding_global_object, "notify_observers");
    const auto signal_set = javascript::environment::realms_2::get<signal_set_t>(nullptr_surrounding_global_object, "signal_slots");
    javascript::environment::realms_2::set(nullptr_surrounding_global_object, "signal_slots", signal_set_t{});

    // iterate every MutationObserver in the 'notify_set'
    for (mutations::mutation_observer* const mo: notify_set)
    {
        // empty the record queue in each MutationObserver, by swapping the list held in the pointer with an empty list;
        // the queue of records is now stored locally
        auto records = std::make_unique<ext::queue<mutations::mutation_record*>>();
        mo->m_record_queue.swap(records);

        // iterate each node in the MutationObserver's node list, and for each transient registered observer (a
        // registered observer who has a source) linked to the node, remove it if its observer is 'mo' - this means that
        // any observers whose 'observer' link is 'mo', and who belong to a node that is tied to 'mo' are removed
        // TODO : why?
        for (const nodes::node* const node: *mo->m_node_list)
            node->m_registered_observer_list = *node->m_registered_observer_list
                    | ranges::views::cast_all_to<transient_registered_observer_t*>()
                    | ranges::views::remove_if([mo](const transient_registered_observer_t* const observer) {return observer->observer.get() == mo;});

        // if there are any MutationRecords from the JavaScript environment, call 'mo''s callback with the list of
        // records, reporting any exceptions that are caught during the process
        if (!records->empty())
        {
            JS_EXCEPTION_HANDLER;
            mo->m_callback(records, mo);

            if (JS_EXCEPTION_HAS_THROWN)
                console::reporting::report_exception(JS_EXCEPTION_MESSAGE)
        }
    }

    // fire a "slotchange" event at every slot in the JavaScript environment list TODO : why
    for (const html::elements::html_slot_element* const slot: signal_set)
        fire_event(slot, "slotchange", {{"bubbles", true}});
}


template <typename F>
auto dom::detail::queue_microtask(
        F&& steps,
        v8::Isolate* event_loop,
        nodes::document* document)
        -> void
{
    JS_BLOCK_ENTER
        JS_REALM_GET_IMPLIED
        // set the 'event loop' and 'document' to the implied objects (via the implied realm) TODO
        event_loop = event_loop ? event_loop : implied_agent;
        document = document ? document : implied_document();

        // create a microtask and assign it the relevant data TODO
        const v8::Local<v8::Function> microtask = v8::Function::New(event_loop->GetCurrentContext(), std::forward<F>(steps));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "source"), microtask->TaskSource());
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "document"), v8pp::to_v8(event_loop, document));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "set"), v8pp::to_v8(event_loop, ext::set<void*>{}));

        // enqueue the microtask to the event loop
        event_loop->EnqueueMicrotask(microtask);
    JS_BLOCK_EXIT
}


auto dom::detail::queue_mutation_record(
        const mutation_type_t type,
        nodes::node* target,
        const std::string& name,
        const std::string& namespace_,
        const std::string& old_value,
        ext::vector<nodes::node*>&& added_nodes,
        ext::vector<nodes::node*>&& removed_nodes,
        nodes::node* previous_sibling,
        nodes::node* next_sibling)
        -> void
{
    using enum mutation_type_t;

    // created a map of MutationObservers to strings, to save observers of interest, and get all the ancestors of the
    // target node, as these nodes' registered observer lists contains the MutationObserver objects that may be of
    // interest
    ext::map<mutations::mutation_observer*, ext::string> interested_observers {};
    auto nodes = ancestors(target);

    // iterate each MutationObserver for each node
    for (nodes::node* node: nodes)
    {
        for (registered_observer_t* registered: *node->m_registered_observer_list)
        {
            // if the conditions based on the 'type' and 'options' dictionary are valid, then modify the
            // 'interested_observers' map
            auto options = registered->options;
            options.try_emplace("attributeFilter", ext::vector<ext::string>{});

            if (type == ATTRIBUTES && options.try_emplace("attributes").second && (ranges::contains(options.at("attributeFilter").to<ext::vector<ext::string>>(), name) || !namespace_.empty())
                || node != target && options.try_emplace("subtree", true).first->second.to<ext::boolean>() == false
                || type == CHILD_LIST && options.try_emplace("childList", true).first->second.to<ext::boolean>() == false
                || type == ATTRIBUTES && options.try_emplace("attributes", true).first->second.to<ext::boolean>() == false
                || type == CHARACTER_DATA && options.try_emplace("characterData", true).first->second.to<ext::boolean>() == false)
            {
                auto mo = registered->observer.get();

                // if the MutationObserver is not in the map, then insert it with an empty string as the corresponding
                // value
                if (!ranges::contains(interested_observers | ranges::views::keys, mo))
                    interested_observers.insert_or_assign(mo, "");

                // if there is a valid old value supplied in the 'options' dictionary that matches the 'type', then set
                // the value of the MutationObserver to the old value
                if (type == ATTRIBUTES && options.try_emplace("attributeOldValue", false).first->second == true
                        || type == CHARACTER_DATA && options.try_emplace("characterDataOldValue", false).first->second == true)
                    interested_observers.insert_or_assign(mo, old_value);
            }
        }
    }

    // iterate over each interested observer, and emplace a mutation record into the observer based on the parameters
    // and the 'mapped_old_value' string
    for (const auto& [observer, mapped_old_value]: interested_observers)
    {
        mutations::mutation_record record;
        record.type = magic_enum::enum_name(type) | ranges::views::lowercase();
        record.attribute_name = name;
        record.attribute_namespace = namespace_;
        record.old_value = mapped_old_value;
        record.target = target;
        record.previous_sibling = previous_sibling;
        record.next_sibling = next_sibling;
        record.added_nodes = &added_nodes;
        record.removed_nodes = &removed_nodes;
        observer->m_record_queue->push(std::move(record));
    }

    // queue a mutation observers microtask
    queue_mutation_observer_microtask();
}


auto dom::detail::queue_tree_mutation_record(
        nodes::node* const target,
        const ext::vector<nodes::node*>& added_nodes,
        const ext::vector<nodes::node*>& removed_nodes,
        nodes::node* const previous_sibling,
        nodes::node* const next_sibling)
        -> void
{
    using enum mutation_type_t;

    // there has to be an element in either the 'added_nodes' or 'removed_nodes' list, as otherwise there is no mutation
    // happening; this method is just a wrapper around 'queue_mutation_record', so call that method with some parameters
    // set to fixed values
    assert(!added_nodes.empty() || !removed_nodes.empty());
    queue_mutation_record(CHILD_LIST, target, "", "", "", added_nodes, removed_nodes, previous_sibling, next_sibling);
}


auto dom::detail::queue_mutation_observer_microtask() -> void
{
    JS_REALM_GET_SURROUNDING(nullptr)

    // get if the surrounding global object's 'mutation_observer_microtask_queued' attribute is set to true; return
    // early if it is, otherwise set it to true, and queue a microtask to 'notify_mutation_observers()'
    const auto queued = javascript::environment::realms_2::get<ext::boolean>(nullptr_surrounding_global_object, "mutation_observer_microtask_queued");
    return_if(queued);
    javascript::environment::realms_2::set(nullptr_surrounding_global_object, "mutation_observer_microtask_queued", true);

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
        JS_REALM_GET_IMPLIED
        event_loop = event_loop ? event_loop : implied_agent;
        document = document ? document : implied_document();

        const v8::Local<v8::Function> microtask = v8::Function::New(event_loop->GetCurrentContext(), std::forward<F>(steps));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "source"), task_source);
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "document"), v8pp::to_v8(event_loop, document));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "set"), v8pp::to_v8(event_loop, ext::set<void*>{}));

        // enqueue the microtask to the event loop
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
    JS_REALM_GET_RELEVANT(global_object)
    const auto* const document = javascript::environment::realms_2::get<ext::string>(global_object, "type") == "Window"
                     ? javascript::environment::realms_2::get<nodes::document*>(global_object, "associated_document")
                     : nullptr;

    queue_task(task_source, std::forward<F>(steps), global_object_relevant_agent, document);
}


template <typename F>
auto dom::detail::queue_element_task(
        html::detail::task_queue_t& task_source,
        const html::elements::html_element* const element,
        F&& steps)
        -> void
{
    JS_REALM_GET_RELEVANT(element)
    queue_global_task(task_source, element_relevant_global_object, std::forward<F>(steps));
}
