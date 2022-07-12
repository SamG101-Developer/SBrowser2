#include "event_target.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/events/event.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/remove_if.hpp>


auto dom::nodes::event_target::add_event_listener(
        ext::string&& type,
        event_listener_callback_t&& callback,
        ext::string_any_map& options)
        -> void
{
    // create an event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::event_internals::flatten_more(options);
    event_listener.insert_or_assign("callback", std::forward<event_listener_callback_t>(callback));
    event_listener.insert_or_assign("type"    , std::forward<ext::string              >(type    ));

    // get the abort signal from the event listener, and default the object to nullptr if it doesn't exist in the map
    auto* signal = event_listener.at("signal").value_to_or<abort::abort_signal*>(nullptr);

    // return if
    //  - there is no callback - invoking the event listener would have no effect and would waste cycles;
    //  - there is a signal that has already aborted - no need for the event listener to exist;
    //  - the event listener is already stored in the event listeners list - no duplicates allowed;
    if (event_listener.at("callback").empty()
            || signal && signal->aborted()
            || ranges::contains(m_event_listeners, event_listener))
        return;

    // append the event listener to the event listeners list and if there is an abort signal, add an abort algorithm
    // that removes the event_listener from the event_target->m_event_listeners list
    m_event_listeners.push_back(event_listener);
    if (signal)
        signal->m_abort_algorithms.push_back(ext::bind_front(event_target::remove_event_listener, this, event_listener));
}


auto dom::nodes::event_target::remove_event_listener(
        ext::string&& type,
        event_listener_callback_t&& callback,
        ext::string_any_map& options)
        -> void
{
    // create a dummy event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::event_internals::flatten_more(options);
    event_listener.insert_or_assign("callback", std::move(callback));
    event_listener.insert_or_assign("type", type);

    // set the removed attribute of the listener to true (so if the listener is being held in a variable it can be
    // detected that it is no longer in use)
    event_listener.insert_or_assign("removed", false);

    // alias the callback type for convenience, and remove all event listeners that have a matching callback, type and
    // capture attribute to event_listener
    using callback_t = typename nodes::event_target::event_listener_callback_t;

    auto event_listener_equality_check = [event_listener](const ext::string_any_map& existing_listener)
    {
        return existing_listener.at("callback").has_value_and_equals(event_listener.at("callback")->to<callback_t>())
               && existing_listener.at("type").has_value_and_equals(event_listener.at("type")->to<ext::string_view>())
               && existing_listener.at("capture").has_value_and_equals(event_listener.at("capture")->to<ext::boolean>());
    };

    m_event_listeners |= ranges::views::remove_if(event_listener_equality_check);
}


auto dom::nodes::event_target::dispatch_event(
        events::event* event)
        -> ext::boolean
{
    // if the dispatch is already set or the initialized flag isn't set, then throw an invalid state error
    detail::exception_internals::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [event] {return event->m_dispatch_flag || not event->m_initialized_flag;},
            "Event must be initialized and not dispatched in order be dispatched");

    // set the event trusted to false (manual dispatch), and dispatch the event through the tree
    event->is_trusted = ext::boolean::FALSE();
    return detail::event_internals::dispatch(event, this);
}


auto dom::nodes::event_target::get_the_parent(
        events::event* event)
        -> event_target*
{
    // default behaviour for getting the parent in event traversal is that there is no parent
    return nullptr;
}


auto dom::nodes::event_target::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<event_target>{isolate}
            .ctor<>()
            .inherit<web_apis::dom_object>()
            .function("addEventListener", &event_target::add_event_listener)
            .function("removeEventListener", &event_target::remove_event_listener)
            .function("dispatchEvent", &event_target::dispatch_event)
            .auto_wrap_objects();
}
