#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_ACTIVE_INFO_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_ACTIVE_INFO_HPP

#include "dom_object.hpp"
namespace webgl2::other {class webgl_active_info;}

#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(webgl2)


class webgl2::other::webgl_active_info
        : public dom_object
{
public constructors:
    DOM_CTORS(webgl_active_info);
    webgl_active_info() = default;
    
public js_properties:
    ext::property<detail::glint_t> size;
    ext::property<detail::glenum_t> type;
    ext::property<ext::string> name;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_ACTIVE_INFO_HPP
