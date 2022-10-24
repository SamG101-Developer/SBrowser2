#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_PROGRAM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_PROGRAM_HPP

#include "webgl_object.hpp"
namespace webgl2::objects {class webgl_program;}
namespace webgl2::objects {class webgl_program_private;}


class webgl2::objects::webgl_program
        : public webgl_object
{
public constructors:
    webgl_program();
    MAKE_PIMPL(webgl_program);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_PROGRAM_HPP
