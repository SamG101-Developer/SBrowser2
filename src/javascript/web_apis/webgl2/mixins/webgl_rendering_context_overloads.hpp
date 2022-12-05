#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_MIXINS_WEBGL_RENDERING_CONTEXT_OVERLOADS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_MIXINS_WEBGL_RENDERING_CONTEXT_OVERLOADS_HPP


namespace webgl2::mixins {class webgl_rendering_context_overloads;}


class webgl2::mixins::webgl_rendering_context_overloads
        : public virtual dom_object
{
public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2_MIXINS_WEBGL_RENDERING_CONTEXT_OVERLOADS_HPP
