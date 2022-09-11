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
            ext::number<double> x, ext::number<double> y) -> void;

    auto line_to(
            ext::number<double> x, ext::number<double> y) -> void;

    auto quadratic_curve_to(
            ext::number<double> cpx, ext::number<double> cpy, ext::number<double> x,
            ext::number<double> y) -> void;

    auto bezier_curve_to(
            ext::number<double> cpx1, ext::number<double> cpy1, ext::number<double> cpx2,
            ext::number<double> cpy2, ext::number<double> x, ext::number<double> y) -> void;

    auto arc_to(
            ext::number<double> x1, ext::number<double> y1, ext::number<double> x2,
            ext::number<double> y2, ext::number<double> radius) -> void;

    auto rect(ext::number<double> x, ext::number<double> y, ext::number<double> w,
              ext::number<double> h) -> void;

    auto rouund_rect(ext::number<double> x, ext::number<double> y, ext::number<double> w,
              ext::number<double> h, ext::vector_view<css::detail::dom_point_init_t> radii = {}) -> void;

    auto arc(ext::number<double> x, ext::number<double> y, ext::number<double> radius,
             ext::number<double> start_angle, ext::number<double> end_angle,
             ext::boolean&& counter_clockwise = false) -> void;

    auto ellipse(ext::number<double> x, ext::number<double> Y, ext::number<double> radius_x,
                 ext::number<double> radius_y, ext::number<double> rotation,
                 ext::number<double> start_angle, ext::number<double> end_angle,
                 ext::boolean&& counter_clockwaise = false) -> void;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean needs_new_subpath = true;
    // TODO : store actual path (QPainterPath)
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_PATH_HPP
