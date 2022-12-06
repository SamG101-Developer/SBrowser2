#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_REQUEST_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_REQUEST_PRIVATE_HPP

#include "ext/pimpl.ixx"



DEFINE_PRIVATE_CLASS(presentation, presentation_request) : dom::nodes::event_target_private
{
    ext::vector<ext::string> presentation_request_urls;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_REQUEST_PRIVATE_HPP
