#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_RECEIVER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_RECEIVER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/promise.ixx"
#include "ext/vector.hpp"
namespace presentation {class presentation_connection;}


DEFINE_PRIVATE_CLASS(presentation, presentation_receiver) : virtual dom_object_private
{
    ext::promise<ext::vector<std::unique_ptr<presentation_connection>>> connection_list;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_RECEIVER_PRIVATE_HPP
