#include "event_target.hpp"

#include "dom/_typedefs.hpp"
#include "ext/functional.hpp"
#include "ext/pimpl.hpp"
#include "ext/ranges.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/events/event.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/remove_if.hpp>
#include <utility>

#include "dom/detail/node_internals.hpp"


dom::nodes::event_target::event_target()
{
    INIT_PIMPL(event_target);
}


auto dom::nodes::event_target::add_event_listener(
        ext::string&& type,
        detail::event_listener_callback_t&& callback,
        ext::variant<detail::add_event_listener_options_t, ext::boolean> options)
        -> void
{
    ACCESS_PIMPL(event_target);

    // create an event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::flatten_more(std::move(options));
    event_listener.insert_or_assign("callback", std::move(callback));
    event_listener.insert_or_assign("type", std::move(type));

    // get the abort signal from the event listener, and default the object to nullptr if it doesn't exist in the map
    decltype(auto) signal = event_listener.try_emplace("signal", nullptr).first->second.to<abort::abort_signal*>();

    // return if
    //  - there is no callback - invoking the event listener would have no effect and would waste cycles;
    //  - there is a signal that has already aborted - no need for the event listener to exist;
    //  - the event listener is already stored in the event listeners list - no duplicates allowed;
    if (!event_listener.contains("callback")
            || signal && signal->aborted()
            || ranges::contains(d->event_listeners, event_listener))
        return;

    // append the event listener to the event listeners list and if there is an abort signal, add an abort algorithm
    // that removes the event_listener from the event_target->m_event_listeners list
    d->event_listeners.push_back(event_listener);
    if (signal)
        signal->m_abort_algorithms.push_back(BIND_FRONT(event_target::remove_event_listener, this, event_listener));
}


auto dom::nodes::event_target::remove_event_listener(
        ext::string&& type,
        detail::event_listener_callback_t&& callback,
        ext::variant<detail::event_listener_options_t, ext::boolean> options)
        -> void
{
    ACCESS_PIMPL(event_target);

    // create a dummy event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::flatten_more(std::move(options));
    event_listener.insert_or_assign("callback", std::move(callback));
    event_listener.insert_or_assign("type", type);

    // set the removed attribute of the listener to true (so if the listener is being held in a variable it can be
    // detected that it is no longer in use)
    event_listener.insert_or_assign("removed", false);

    // alias the callback type for convenience, and remove all event listeners that have a matching callback, type and
    // capture attribute to event_listener
    auto event_listener_equality_check = [event_listener](ext::map<ext::string, ext::any>&& e)
    {
        using callback_t = detail::event_listener_callback_t;
        return e.try_emplace("callback", nullptr).first->second.to<callback_t>() == event_listener.at("callback").to<callback_t>()
                && e.try_emplace("type", nullptr).first->second.to<ext::string_view>() == event_listener.at("type").to<ext::string_view>()
                && e.try_emplace("capture", nullptr).first->second.to<ext::boolean>() == event_listener.at("capture").to<ext::boolean>();
    };

    d->event_listeners |= ranges::actions::remove_if(event_listener_equality_check);
}


auto dom::nodes::event_target::dispatch_event(
        events::event* event)
        -> ext::boolean
{
    ACCESS_PIMPL(event_target);
    using enum dom::detail::dom_exception_error_t;

    // if the dispatch is already set or the initialized flag isn't set, then throw an invalid state error
    detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [event] {return event->d_func()->dispatch_flag || !event->d_func()->initialized_flag;},
            "Event must be initialized and not dispatched in order be dispatched");

    // set the event trusted to false (manual dispatch), and dispatch the event through the tree
    event->d_func()->is_trusted = ext::boolean::FALSE_();
    return detail::dispatch(event, this);
}


auto dom::nodes::event_target::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<event_target>{isolate}
            .ctor<>()
            .inherit<dom_object>()
            .function("addEventListener", &event_target::add_event_listener)
            .function("removeEventListener", &event_target::remove_event_listener)
            .function("dispatchEvent", &event_target::dispatch_event)
            .auto_wrap_objects();

    return std::move(conversion);
}
