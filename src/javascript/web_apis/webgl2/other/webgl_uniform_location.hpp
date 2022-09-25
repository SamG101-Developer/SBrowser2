#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_HPP

#include "dom_object.hpp"
namespace webgl2::other {class webgl_uniform_location;}


class webgl2::other::webgl_uniform_location
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(webgl_uniform_location);
    webgl_uniform_location() = default;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_UNIFORM_LOCATION_HPP
