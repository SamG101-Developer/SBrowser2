#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_PROGRAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_PROGRAM_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "webgl2/objects/webgl_object.hpp"

#include <QtOpenGL/QOpenGLShaderProgram>


DEFINE_PRIVATE_CLASS(webgl2::objects, webgl_program) : webgl2::objects::webgl_object
{
    std::unique_ptr<QOpenGLShaderProgram> gl;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_PROGRAM_PRIVATE_HPP
