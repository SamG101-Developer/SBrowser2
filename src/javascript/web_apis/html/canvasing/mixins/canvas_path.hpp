#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_path;}

#include USE_INNER_TYPES(css/geometry)


class html::canvasing::mixins::canvas_path
        : public virtual dom_object
{
public js_methods:
    auto close_path()
            -> void;

    auto move_to(
            const ext::number<double>& x, const ext::number<double>& y) -> void;

    auto line_to(
            const ext::number<double>& x, const ext::number<double>& y) -> void;

    auto quadratic_curve_to(
            const ext::number<double>& cpx, const ext::number<double>& cpy, const ext::number<double>& x,
            const ext::number<double>& y) -> void;

    auto bezier_curve_to(
            const ext::number<double>& cpx1, const ext::number<double>& cpy1, const ext::number<double>& cpx2,
            const ext::number<double>& cpy2, const ext::number<double>& x, const ext::number<double>& y) -> void;

    auto arc_to(
            const ext::number<double>& x1, const ext::number<double>& y1, const ext::number<double>& x2,
            const ext::number<double>& y2, const ext::number<double>& radius) -> void;

    auto rect(const ext::number<double>& x, const ext::number<double>& y, const ext::number<double>& w,
              const ext::number<double>& h) -> void;

    auto rouund_rect(const ext::number<double>& x, const ext::number<double>& y, const ext::number<double>& w,
              const ext::number<double>& h, ext::vector_view<css::detail::dom_point_init_t> radii = {}) -> void;

    auto arc(const ext::number<double>& x, const ext::number<double>& y, const ext::number<double>& radius,
             const ext::number<double>& start_angle, const ext::number<double>& end_angle,
             ext::boolean&& counter_clockwise = false) -> void;

    auto ellipse(const ext::number<double>& x, const ext::number<double>& Y, const ext::number<double>& radius_x,
                 const ext::number<double>& radius_y, const ext::number<double>& rotation,
                 const ext::number<double>& start_angle, const ext::number<double>& end_angle,
                 ext::boolean&& counter_clockwaise = false) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_HPP
