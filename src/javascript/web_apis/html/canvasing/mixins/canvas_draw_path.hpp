#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_PATH_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_PATH_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_draw_path;}

#include USE_INNER_TYPES(html)
namespace html::canvasing {class path_2d;}


class html::canvasing::mixins::canvas_draw_path
        : public virtual dom_object
{
public js_methods:
    auto begin_path() -> void;
    auto fill(detail::canvas_fill_rule_t fill_rule = detail::canvas_fill_rule_t::NONZERO) -> void;
    auto fill(path_2d* path, detail::canvas_fill_rule_t fill_rule = detail::canvas_fill_rule_t::NONZERO) -> void;
    auto stroke() -> void;
    auto stroke(path_2d* path) -> void;
    auto clip(detail::canvas_fill_rule_t fill_rule = detail::canvas_fill_rule_t::NONZERO) -> void;
    auto clip(path_2d* path, detail::canvas_fill_rule_t fill_rule = detail::canvas_fill_rule_t::NONZERO) -> void;
    auto is_point_in_path(const ext::number<double>& x, const ext::number<double>& y, detail::canvas_fill_rule_t fill_rule = detail::canvas_fill_rule_t::NONZERO) -> ext::boolean;
    auto is_point_in_path(path_2d* path, const ext::number<double>& x, const ext::number<double>& y, detail::canvas_fill_rule_t fill_rule = detail::canvas_fill_rule_t::NONZERO) -> ext::boolean;
    auto is_point_in_stroke(const ext::number<double>& x, const ext::number<double>& y) -> ext::boolean;
    auto is_point_in_stroke(path_2d* path, const ext::number<double>& x, const ext::number<double>& y) -> ext::boolean;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_PATH_HPP
