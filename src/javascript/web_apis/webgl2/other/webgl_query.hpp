#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_QUERY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_QUERY_HPP

#include "webgl2/objects/webgl_object.hpp"
namespace webgl2::other {class webgl_query;}


class webgl2::other::webgl_query
        : public objects::webgl_object
{
public constructors:
    DOM_CTORS(webgl_query);
    webgl_query() = default;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_QUERY_HPP
