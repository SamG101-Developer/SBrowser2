#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_STATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_STATE_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_state;}


class html::canvasing::mixins::canvas_state
        : public virtual dom_object
{
public js_methods:
    auto save() -> void;
    auto restore() -> void;
    auto reset() -> void;
    auto is_context_lost() -> void;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    // TODO : m_drawing-state-stack
    ext::boolean m_context_lost;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_STATE_HPP
