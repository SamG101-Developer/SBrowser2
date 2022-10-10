#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_CLOSE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_CLOSE_EVENT_HPP

// Inheritance Includes & This Class
#include "dom/events/event.hpp"
namespace presentation {class presentation_connection_close_event;}
namespace presentation {class presentation_connection_close_event_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(presentation)


class presentation::presentation_connection_close_event
        : public dom::events::event
{
public constructors:
    presentation_connection_close_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(presentation_connection_close_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(reason, detail::presentation_connection_close_reason);
    DEFINE_GETTER(message, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_CLOSE_EVENT_HPP
