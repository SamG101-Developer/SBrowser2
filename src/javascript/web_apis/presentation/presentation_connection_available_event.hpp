#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_AVAILABLE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_AVAILABLE_EVENT_HPP

// Inheritance Includes & This Class
#include "dom/events/event.hpp"
namespace presentation {class presentation_connection_available_event;}
namespace presentation {class presentation_connection_available_event_private;}

// Other Includes & Forward Declarations
namespace presentation {class presentation_connection;}


class presentation::presentation_connection_available_event
        : public dom::events::event
{
public constructors:
    presentation_connection_available_event();
    presentation_connection_available_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(presentation_connection_available_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(connection, presentation_connection*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_AVAILABLE_EVENT_HPP
