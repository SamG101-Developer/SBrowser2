#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SHADER_PRECISION_FORMAT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SHADER_PRECISION_FORMAT_HPP

#include "dom_object.hpp"
namespace webgl2::other {class webgl_shader_precision_format;}

#include INCLUDE_INNER_TYPES(webgl2)


class webgl2::other::webgl_shader_precision_format
        : public dom_object
{
public constructors:
    DOM_CTORS(webgl_shader_precision_format);
    webgl_shader_precision_format() = default;
    
public js_properties:
    ext::property<detail::glint_t> range_min;
    ext::property<detail::glint_t> range_max;
    ext::property<detail::glint_t> precision;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SHADER_PRECISION_FORMAT_HPP
