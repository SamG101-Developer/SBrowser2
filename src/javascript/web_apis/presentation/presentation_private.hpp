#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

namespace presentation {class presentation_request;}
namespace presentation {class presentation_receiver;}


DEFINE_PRIVATE_CLASS(presentation, presentation) : virtual dom_object_private
{
    std::unique_ptr<presentation::presentation_request> presentation_request;
    std::unique_ptr<presentation::presentation_receiver> presentation_receiver;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_PRIVATE_HPP
