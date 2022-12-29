module;
#include "ext/macros.hpp"


module apis.dom.event_target:p;
import apis.dom.event_target;
import apis.dom.event;
import apis.dom.types;

import ext.core;


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
