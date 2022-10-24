#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_HPP

#include "dom_object.hpp"
namespace webgl2::other {class webgl_uniform_location;}
namespace webgl2::other {class webgl_uniform_location_private;}


class webgl2::other::webgl_uniform_location
        : public virtual dom_object
{
public constructors:
    webgl_uniform_location();
    MAKE_PIMPL(webgl_uniform_location);
    MAKE_V8_AVAILABLE;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_HPP
