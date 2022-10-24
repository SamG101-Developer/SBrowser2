#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_MIXINS_WEBGL2_RENDERING_CONTEXT_BASE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_MIXINS_WEBGL2_RENDERING_CONTEXT_BASE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(webgl2)


DEFINE_PRIVATE_CLASS(webgl2::mixins, webgl2_rendering_context_base) : virtual dom_object_private
{
    std::unique_ptr<detail::gl_base> gl;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_MIXINS_WEBGL2_RENDERING_CONTEXT_BASE_PRIVATE_HPP
