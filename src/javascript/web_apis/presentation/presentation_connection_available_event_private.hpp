#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_AVAILABLE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_AVAILABLE_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"


namespace presentation {class presentation_connection;}


DEFINE_PRIVATE_CLASS(presentation, presentation_connection_available_event) : dom::events::event_private
{
    presentation_connection* connection;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_AVAILABLE_EVENT_PRIVATE_HPP
