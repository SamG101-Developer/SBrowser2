#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_PATTERN_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_PATTERN_HPP


namespace html::canvasing {class canvas_pattern;}

#include INCLUDE_INNER_TYPES(css/geometry)


class html::canvasing::canvas_pattern
        : public virtual dom_object
{
public constructors:
    canvas_pattern() = default;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

public js_methods:
    auto set_transform(css::detail::dom_matrix2d_init_t&& transform = {});
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_PATTERN_HPP
