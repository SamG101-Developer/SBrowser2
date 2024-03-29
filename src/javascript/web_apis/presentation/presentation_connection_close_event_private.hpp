#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_CLOSE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_CLOSE_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(presentation)



DEFINE_PRIVATE_CLASS(presentation, presentation_connection_close_event) : dom::events::event_private
{
    detail::presentation_connection_close_reason reason;
    ext::string message;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_CLOSE_EVENT_PRIVATE_HPP
