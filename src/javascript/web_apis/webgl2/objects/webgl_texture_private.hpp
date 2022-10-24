#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "webgl2/objects/webgl_object_private.hpp"

#include <QtOpenGL/QOpenGLTexture>


DEFINE_PRIVATE_CLASS(webgl2::objects, webgl_texture) : webgl_object_private
{
    std::unique_ptr<QOpenGLTexture> gl;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_PRIVATE_HPP
