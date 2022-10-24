#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_HPP

#include "webgl_object.hpp"
namespace webgl2::objects {class webgl_texture;}
namespace webgl2::objects {class webgl_texture_private;}


class webgl2::objects::webgl_texture
        : public webgl_object
{
public constructors:
    webgl_texture();
    MAKE_PIMPL(webgl_texture);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OBJECTS_WEBGL_TEXTURE_HPP
