#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_HPP

#include "svg/elements/svg_graphics_element.hpp"
namespace svg::elements {class svg_geometry_element;}
namespace svg::elements {class svg_geometry_element_private;}

#include INCLUDE_INNER_TYPES(css/geometry)

namespace css::geometry {class dom_point;}
namespace svg::types {class svg_animated_number;}


class svg::elements::svg_geometry_element
        : public svg_graphics_element
{
public constructors:
    DOM_CTORS(svg_geometry_element);
    MAKE_PIMPL(svg_geometry_element);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto is_point_in_fill(css::detail::dom_point_init_t&& point = {}) -> ext::boolean;
    auto is_point_in_stroke(css::detail::dom_point_init_t&& point = {}) -> ext::boolean;
    auto get_total_length() -> ext::number<float>;
    auto get_point_at_length() -> css::geometry::dom_point;

private js_properties:
    DEFINE_GETTER(path_length, types::svg_animated_number*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GEOMETRY_ELEMENT_HPP
