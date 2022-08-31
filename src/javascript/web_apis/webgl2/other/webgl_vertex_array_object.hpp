#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_VERTEX_ARRAY_OBJECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_VERTEX_ARRAY_OBJECT_HPP

#include "webgl2/objects/webgl_object.hpp"
namespace webgl2::other {class webgl_vertex_array_object;}


class webgl2::other::webgl_vertex_array_object
        : public objects::webgl_object
{
public constructors:
    DOM_CTORS(webgl_vertex_array_object);
    webgl_vertex_array_object() = default;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_VERTEX_ARRAY_OBJECT_HPP
