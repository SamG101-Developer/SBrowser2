module;
#include "ext/macros/pimpl.hpp"
#include <utility>


module apis.dom.event_target_private;
import apis.dom.event_target;
import apis.dom.event;
import apis.dom.types;

import ext.any;
import ext.boolean;
import ext.concepts;
import ext.map;
import ext.string;


auto dom::event_target_private::remove_all_event_listeners() -> void
{
    // Iterate over the event listeners of the 'event_target', and remove each listener from the 'event_target' using
    // the predefined removal algorithm defined in the EventTarget class.
    ACCESS_QIMPL;
    for (decltype(auto) existing_listener: event_listeners)
        q->remove_event_listener(
                existing_listener.at(u"type").to<ext::string>(),
                existing_listener.at(u"callback").to<detail::event_listener_callback_t>(),
                std::move(existing_listener));
}


template <ext::inherit<dom::event> T>
auto dom::event_target_private::fire_event(ext::string&& e, ext::map<ext::string, ext::any>&& init) -> ext::boolean
{
    // create a new event of type T, setting the event type and options, and then dispatch it to 'target'
    ACCESS_QIMPL;
    auto event  = std::make_unique<T>(std::move(e), std::move(init));
    return dispatch(std::move(event), q);
}
