#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_HPP

#include "svg/elements/svg_graphics_element.hpp"
namespace svg::elements {class svg_geometry_element;}

#include "ext/boolean.hpp"
#include USE_INNER_TYPES(css/geometry)
namespace css::geometry {class dom_point;}


class svg::elements::svg_geometry_element
        : public svg_graphics_element
{
public constructors:
    DOM_CTORS(svg_geometry_element);
    svg_geometry_element() = default;

public js_methods:
    auto is_point_in_fill(css::geometry::detail::dom_point_init_t&& point = {}) -> ext::boolean;
    auto is_point_in_stroke(css::geometry::detail::dom_point_init_t&& point = {}) -> ext::boolean;
    auto get_total_length() -> ext::number<float>;
    auto get_point_at_length() -> css::geometry::dom_point;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_HPP
