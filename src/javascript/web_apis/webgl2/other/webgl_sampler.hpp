#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SAMPLER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SAMPLER_HPP

#include "webgl2/objects/webgl_object.hpp"
namespace webgl2::other {class webgl_sampler;}


class webgl2::other::webgl_sampler
        : public objects::webgl_object
{
public constructors:
    DOM_CTORS(webgl_sampler);
    webgl_sampler() = default;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_OTHER_WEBGL_SAMPLER_HPP
