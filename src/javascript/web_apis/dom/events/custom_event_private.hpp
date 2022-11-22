#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_CUSTOM_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_CUSTOM_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event_private.hpp"

#include "ext/any.hpp"


DEFINE_PRIVATE_CLASS(dom::events, custom_event)
        : event_private
{
    MAKE_QIMPL(custom_event);

    ext::any detail;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_EVENTS_CUSTOM_EVENT_PRIVATE_HPP
