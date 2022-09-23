#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_DRAWING_STYLES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_DRAWING_STYLES_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_path_drawing_styles;}

#include INCLUDE_INNER_TYPES(html)


class html::canvasing::mixins::canvas_path_drawing_styles
        : public virtual dom_object
{
public js_methods:
    auto set_line_dash(const ext::vector<ext::number<double>>& segments) -> void;
    auto get_line_dash() -> const ext::vector<ext::number<double>>&;

private js_properties:
    ext::property<ext::number<double>> line_dash_offset;
    ext::property<ext::number<double>> line_width;
    ext::property<ext::number<double>> miter_limit;
    ext::property<detail::canvas_line_cap_t> line_cap;
    ext::property<detail::canvas_line_join_t> line_join;

public cpp_properties:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_DRAWING_STYLES_HPP
