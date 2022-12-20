module;
#include "ext/macros/pimpl.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/remove_if.hpp>
#include <swl/variant.hpp>
#include <utility>


module apis.dom.event_target;
import apis.dom.abort_signal;
import apis.dom.detail;
import apis.dom.types;
import ext.core;


dom::event_target::event_target()
{
    INIT_PIMPL;
}


template <ext::type_is<detail::add_event_listener_options_t, ext::boolean T>
auto dom::event_target::add_event_listener(
        ext::string&& type,
        detail::event_listener_callback_t&& callback,
        T&& options)
        -> void
{
    ACCESS_PIMPL;

    // Create an event listener that is the flattened options, and insert the callback and type.
    auto event_listener = detail::flatten_more(std::forward<T>(options));
    event_listener.insert_or_assign(u"callback", std::move(callback));
    event_listener.insert_or_assign(u"type", std::move(type));

    // Get the abort signal from the event listener, and default the object to nullptr if it doesn't exist in the map.
    decltype(auto) signal = event_listener[u"signal"].to<abort::abort_signal*>();

    // Return if any of the following conditions are true:
    //  - There is no callback -- invoking the event listener would have no effect and would waste cycles;
    //  - There is a signal that has already aborted -- no need for the event listener to exist;
    //  - The event listener is already stored in the event listeners list -- no duplicates allowed;
    if (!event_listener.contains(u"callback")
            || signal && signal->d_func()->aborted()
            || ranges::contains(d->event_listeners, event_listener))
        return;

    // Append the event listener to the event listeners list and if there is an abort signal, add an abort algorithm
    // that removes the event_listener from the event_target->d_func()->event_listeners list.
    d->event_listeners.emplace_back(std::move(event_listener));
    if (signal)
        signal->d_func()->abort_algorithms.emplace_back(BIND_FRONT(event_target::remove_event_listener, this, event_listener));
}


template <ext::type_is<detail::event_listener_options_t, ext::boolean> T>
auto dom::event_target::remove_event_listener(
        ext::string&& type,
        detail::event_listener_callback_t&& callback,
        T&& options)
        -> void
{
    ACCESS_PIMPL(event_target);

    // Create a dummy event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::flatten_more(std::forward<T>(options));
    event_listener.insert_or_assign(u"callback", std::move(callback));
    event_listener.insert_or_assign(u"type", std::move(type));

    // Set the removed attribute of the listener to true (so if the listener is being held in a variable it can be
    // detected that it is no longer in use)
    event_listener.insert_or_assign(u"removed", ext::boolean::FALSE_());

    // Alias the callback type for convenience, and remove all event listeners that have a matching callback, type and
    // capture attribute to event_listener
    auto event_listener_equality_check = [event_listener](ext::map<ext::string, ext::any>&& e)
    {
        using callback_t = detail::event_listener_callback_t;
        return e[u"callback"].to<callback_t>() == event_listener.at(u"callback").to<callback_t>()
                && e[u"type"].to<ext::string_view>() == event_listener.at(u"type").to<ext::string_view>()
                && e[u"capture"].to<ext::boolean>() == event_listener.at(u"capture").to<ext::boolean>();
    };

    d->event_listeners |= ranges::actions::remove_if(event_listener_equality_check);
}


auto dom::event_target::dispatch_event(
        event* event)
        -> ext::boolean
{
    ACCESS_PIMPL(event_target);
    using enum dom::detail::dom_exception_error_t;

    // If the dispatch is already set or the initialized flag isn't set, then throw an invalid state error
    detail::throw_v8_exception<INVALID_STATE_ERR>(
            [event] {return event->d_func()->dispatch_flag || !event->d_func()->initialized_flag;},
            u8"Event must be initialized and not dispatched in order be dispatched");

    // Set the event trusted to false (manual dispatch), and dispatch the event through the tree
    event->d_func()->is_trusted = false;
    return detail::dispatch(event, this);
}


auto dom::event_target::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .ctor<>()
        .inherit<dom_object>()
        .function("addEventListener", &event_target::add_event_listener)
        .function("removeEventListener", &event_target::remove_event_listener)
        .function("dispatchEvent", &event_target::dispatch_event)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
