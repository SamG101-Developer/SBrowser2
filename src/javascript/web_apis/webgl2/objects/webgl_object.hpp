#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_OBJECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_OBJECT_HPP


namespace webgl2::objects {class webgl_object;}


class webgl2::objects::webgl_object
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(webgl_object);
    webgl_object() = default;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_invalidated_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_OBJECT_HPP
