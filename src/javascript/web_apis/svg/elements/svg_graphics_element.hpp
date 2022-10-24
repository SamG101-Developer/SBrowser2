#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_HPP

#include "svg/elements/svg_element.hpp"
namespace svg::elements {class svg_graphics_element;}
namespace svg::elements {class svg_graphics_element_private;}

#include INCLUDE_INNER_TYPES(svg)
namespace css::geometry {class dom_rect;}
namespace svg::types {class svg_animated_transform_list;}


class svg::elements::svg_graphics_element
        : public svg_element
        , public mixins::svg_tests
{
public constructors:
    DOM_CTORS(svg_graphics_element);
    MAKE_PIMPL(svg_graphics_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto get_b_box(detail::svg_bounding_box_options_t&& options = {}) -> css::geometry::dom_rect*;
    auto get_ctm() -> css::geometry::dom_rect*;
    auto get_screen_ctm() -> css::geometry::dom_rect*;

public js_properties:
    DEFINE_GETTER(transform, types::svg_animated_transform_list*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_GRAPHICS_ELEMENT_HPP
