#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_HPP

#include "svg/elements/svg_element.hpp"
namespace svg::elements {class svg_graphics_element;}

#include INCLUDE_INNER_TYPES(svg)
namespace css::geometry {class dom_rect;}


class svg::elements::svg_graphics_element
        : public svg_element
        , public mixins::svg_tests
{
public constructors:
    DOM_CTORS(svg_graphics_element);
    svg_graphics_element() = default;

public js_methods:
    auto get_b_box(detail::svg_bounding_box_options_t&& options = {}) -> css::geometry::dom_rect*;
    auto get_ctm() -> css::geometry::dom_rect*;
    auto get_screen_ctm() -> css::geometry::dom_rect*;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_HPP
