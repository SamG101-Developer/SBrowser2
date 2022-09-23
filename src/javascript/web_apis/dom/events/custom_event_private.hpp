#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_CUSTOM_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_CUSTOM_EVENT_PRIVATE_HPP

#include "dom/events/event_private.hpp"

#include "ext/any.hpp"
#include "ext/pimpl.hpp"


DEFINE_PRIVATE_CLASS(dom::events, custom_event) : event_private
{
    ext::any detail;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_CUSTOM_EVENT_PRIVATE_HPP
