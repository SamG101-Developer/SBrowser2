#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(presentation)


DEFINE_PRIVATE_CLASS(presentation, presentation_connection) : dom::nodes::event_target_private
{
    ext::string presentation_identifier;
    ext::string presentation_url;
    detail::presentation_connection_state_t current_state;

    ext::string binary_type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_CONNECTION_PRIVATE_HPP
