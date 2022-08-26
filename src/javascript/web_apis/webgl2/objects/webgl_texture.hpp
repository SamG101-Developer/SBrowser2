#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_HPP

#include "webgl_object.hpp"
namespace webgl2::objects {class webgl_texture;}


class webgl2::objects::webgl_texture
        : public webgl_object
{
public constructors:
    DOM_CTORS(webgl_texture);
    webgl_texture() = default;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_HPP
