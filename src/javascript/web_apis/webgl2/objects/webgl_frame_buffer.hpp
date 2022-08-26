#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_FRAME_BUFFER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_FRAME_BUFFER_HPP

#include "webgl_object.hpp"
namespace webgl2::objects {class webgl_frame_buffer;}


class webgl2::objects::webgl_frame_buffer
        : public webgl_object
{
public constructors:
    DOM_CTORS(webgl_frame_buffer);
    webgl_frame_buffer() = default;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_FRAME_BUFFER_HPP
