#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SYNC_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SYNC_HPP

#include "webgl2/objects/webgl_object.hpp"
namespace webgl2::other {class webgl_sync;}


class webgl2::other::webgl_sync
        : public objects::webgl_object
{
public constructors:
    DOM_CTORS(webgl_sync);
    webgl_sync() = default;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SYNC_HPP
