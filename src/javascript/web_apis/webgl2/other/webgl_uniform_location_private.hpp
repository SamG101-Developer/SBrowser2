#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(webgl2::other, webgl_uniform_location) : virtual dom_object_private
{
    ext::number<int> location_id;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_PRIVATE_HPP
