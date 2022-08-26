#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_CONTEXTS_WEBGL_RENDERING_CONTEXT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_CONTEXTS_WEBGL_RENDERING_CONTEXT_HPP

#include "webgl2/mixins/webgl_rendering_context_base.hpp"
#include "webgl2/mixins/webgl_rendering_context_overloads.hpp"

namespace webgl2::contexts {class webgl_rendering_context;}


class webgl2::contexts::webgl_rendering_context
        : public mixins::webgl_rendering_context_base
        , public mixins::webgl_rendering_context_overloads
{};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_CONTEXTS_WEBGL_RENDERING_CONTEXT_HPP
