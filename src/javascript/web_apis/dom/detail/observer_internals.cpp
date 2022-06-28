#include "observer_internals.hpp"

#include <ext/ranges.hpp>
#include <javascript/environment/realms_2.hpp>

#include <web_apis/dom/detail/event_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
#include <web_apis/dom/mutations/mutation_observer.hpp>
#include <web_apis/dom/mutations/mutation_record.hpp>
#include <web_apis/dom/nodes/document.hpp>

#include <magic_enum.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/map.hpp>

namespace html::elements {class html_slot_element;}


auto dom::detail::observer_internals::notify_mutation_observers() -> void
{
    // set the 'mutation_observer_microtask_queued' variable to false, and get the 'notify_set' (MutationObserver set),
    // and the signal set (HTMLSlotElement set). clear the 'signal_set' in the environment (clone is saved locally)

    JS_REALM_GET_SURROUNDING(nullptr)
    using notify_set_t = ext::set<mutations::mutation_observer*>;
    using signal_set_t = ext::set<html::elements::html_slot_element*>;

    javascript::environment::realms_2::set(surrounding_global_object, "mutation_observer_microtask_queued", false);
    auto notify_set = javascript::environment::realms_2::get<notify_set_t>(surrounding_global_object, "notify_observers");
    auto signal_set = javascript::environment::realms_2::get<signal_set_t>(surrounding_global_object, "signal_slots");
    javascript::environment::realms_2::set(surrounding_global_object, "signal_slots", signal_set_t{});

    // iterate every MutationObserver in the 'notify_set'
    for (mutations::mutation_observer* mo: notify_set)
    {

        // empty the record queue in each MutationObserver, by swapping the list held in the pointer with an empty list;
        // the queue of records is now stored locally
        std::queue<mutations::mutation_record> records;
        mo->m_record_queue->swap(records);

        // iterate each node in the MutationObserver's node list, and for each transient registered observer (a
        // registered observer who has a source) linked to the node, remove it if its observer is 'mo' - this means that
        // any observers whose 'observer' link is 'mo', and who belong to a node that is tied to 'mo' are removed
        // TODO : why?
        for (nodes::node* node: *mo->m_node_list)
            *node->m_registered_observer_list
                    |= ranges::views::cast_all_to<transient_registered_observer>()
                    | ranges::views::remove_if([mo](transient_registered_observer* observer) {return observer->observer.get() == mo;});

        // if there are any MutationRecords from the JavaScript environment, call 'mo''s callback with the list of
        // records, reporting any exceptions that are caught during the process
        if (!records.empty())
        {
            JS_EXCEPTION_HANDLER;
            mo->m_callback(records, mo);

            if (JS_EXCEPTION_HAS_THROWN)
                console::reporting::report_exception(JS_EXCEPTION_MESSAGE)
        }
    }

    // fire a "slotchange" event at every slot in the JavaScript environment list TODO : why
    for (html::elements::html_slot_element* slot: signal_set)
        event_internals::fire_event<>(slot, "slotchange", {"bubbles", true});
}


auto dom::detail::observer_internals::queue_microtask(
        steps_t&& steps,
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
        v8::Local<v8::Function> microtask = v8::Function::New(event_loop->GetCurrentContext(), steps);
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "source")  , microtask->TaskSource());
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "document"), v8pp::to_v8(event_loop, document));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "set"), v8pp::to_v8(event_loop, ext::set<void*>{}));

        // enqueue the microtask to the event loop
        event_loop->EnqueueMicrotask(microtask);
    JS_BLOCK_EXIT
}


auto dom::detail::observer_internals::queue_mutation_record(
        mutation_type_t type,
        nodes::node* target,
        ext::string_view name,
        ext::string_view namespace_,
        ext::string_view old_value,
        const ext::vector<nodes::node*>& added_nodes,
        const ext::vector<nodes::node*>& removed_nodes,
        nodes::node* previous_sibling,
        nodes::node* next_sibling)
        -> void
{
    // created a map of MutationObservers to strings, to save observers of interest, and get all the ancestors of the
    // target node, as these nodes' registered observer lists contains the MutationObserver objects that may be of
    // interest
    ext::map<mutations::mutation_observer*, ext::string> interested_observers {};
    auto nodes = tree_internals::ancestors(target);

    // iterate each MutationObserver for each node
    for (nodes::node* node: nodes)
    {
        for (registered_observer* registered: *node->m_registered_observer_list)
        {
            // if the conditions based on the 'type' and 'options' dictionary are valid, then modify the
            // 'interested_observers' map
            auto options = registered->options;
            if (type == ATTRIBUTES && options.at("attributes").has_value() && (ranges::contains(options.at("attributeFilter").value_to_or<ext::string_vector>({}), name) || namespace_)
                || node != target && options.at("subtree").has_value_and_equals(false)
                || type == CHILD_LIST && options.at("childList").has_value_and_equals(false)
                || type == ATTRIBUTES && options.at("attributes").empty_or_equals(false)
                || type == CHARACTER_DATA && options.at("characterData").empty_or_equals(false))
            {
                auto mo = registered->observer.get();

                // if the MutationObserver is not in the map, then insert it with an empty string as the corresponding
                // value
                if (!ranges::contains(interested_observers | ranges::views::keys, mo))
                    interested_observers.insert_or_assign(mo, "");

                // if there is a valid old value supplied in the 'options' dictionary that matches the 'type', then set
                // the value of the MutationObserver to the old value
                if (type == ATTRIBUTES && options.at("attributeOldValue").has_value_and_equals(true) || type == CHARACTER_DATA && options.at("characterDataOldValue").has_value_and_equals(true))
                    interested_observers.insert_or_assign(mo, old_value);
            }
        }
    }

    // iterate over each interested observer, and emplace a mutation record into the observer based on the parameters
    // and the 'mapped_old_value' string
    for (const auto& [observer, mapped_old_value]: interested_observers)
        observer->m_record_queue->emplace(
                magic_enum::enum_name(type) | ranges::views::transform([](char c) {return tolower(c);}),
                name, namespace_, mapped_old_value, target,
                previous_sibling, next_sibling, added_nodes, removed_nodes);

    // queue a mutation observers microtask
    queue_mutation_observer_microtask();
}


auto dom::detail::observer_internals::queue_tree_mutation_record(
        nodes::node* target,
        const ext::vector<nodes::node*>& added_nodes,
        const ext::vector<nodes::node*>& removed_nodes,
        nodes::node* previous_sibling,
        nodes::node* next_sibling)
        -> void
{
    // there has to be an element in either the 'added_nodes' or 'removed_nodes' list, as otherwise there is no mutation
    // happening; this method is just a wrapper around 'queue_mutation_record', so call that method with some parameters
    // set to fixed values
    assert(!added_nodes.empty() || !removed_nodes.empty());
    queue_mutation_record(CHILD_LIST, target, "", "", "", added_nodes, removed_nodes, previous_sibling, next_sibling);
}


auto dom::detail::observer_internals::queue_mutation_observer_microtask() -> void
{
    JS_REALM_GET_SURROUNDING(nullptr)

    // get if the surrounding global object's 'mutation_observer_microtask_queued' attribute is set to true; return
    // early if it is, otherwise set it to true, and queue a microtask to 'notify_mutation_observers()'
    auto queued = javascript::environment::realms_2::get<ext::boolean>(surrounding_global_object, "mutation_observer_microtask_queued");
    return_if(queued);
    javascript::environment::realms_2::set(surrounding_global_object, "mutation_observer_microtask_queued", true);

    queue_microtask(&notify_mutation_observers);
}


auto dom::detail::observer_internals::queue_task(
        v8::Task& task_source,
        steps_t&& steps,
        v8::Isolate* event_loop,
        nodes::document* document)
        -> void
{
    JS_BLOCK_ENTER
        JS_REALM_GET_IMPLIED
        event_loop = event_loop ? event_loop : implied_agent;
        document = document ? document : implied_document();

        v8::Local<v8::Function> microtask = v8::Function::New(event_loop->GetCurrentContext(), steps);
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "source"), task_source);
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "document"), v8pp::to_v8(event_loop, document));
        microtask->Set(event_loop->GetCurrentContext(), v8pp::to_v8(event_loop, "set"), v8pp::to_v8(event_loop, ext::set<void*>{}));

        // enqueue the microtask to the event loop
        event_loop->EnqueueMicrotask(microtask);
    JS_BLOCK_EXIT
}


auto dom::detail::observer_internals::queue_global_task(
        v8::Task& task_source,
        v8::Local<v8::Object> global_object,
        steps_t&& steps)
        -> void
{
    JS_REALM_GET_RELEVANT(global_object);
    auto* document = javascript::environment::realms_2::get<ext::string>(global_object, "type") == "Window"
                     ? javascript::environment::realms_2::get<nodes::document*>(global_object, "associated_document")
                     : nullptr;

    queue_task(task_source, std::forward<steps_t>(steps), relevant_agent, document);
}


auto dom::detail::observer_internals::queue_element_task(
        v8::Task& task_source,
        html::elements::html_element* element,
        steps_t&& steps)
        -> void
{
    JS_REALM_GET_RELEVANT(element)
    queue_global_task(task_source, relevant_global_object, std::forward<steps_t>(steps));
}
