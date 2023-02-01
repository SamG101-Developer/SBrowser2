#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_STATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_STATE_HPP


namespace html::canvasing::mixins {class canvas_state;}


#include INCLUDE_INNER_TYPES(html)


class html::canvasing::mixins::canvas_state
        : public virtual dom_object
{
private js_methods:
    auto save() -> void;
    auto restore() -> void;
    auto reset() -> void;
    auto is_context_lost() -> ext::boolean;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<detail::drawing_state_t> m_current_drawing_state;
    ext::stack<std::unique_ptr<detail::drawing_state_t>> m_drawing_state_stack;
    ext::boolean m_context_lost = false;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_STATE_HPP
