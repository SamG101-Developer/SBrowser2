#ifndef SBROWSER2_SVG_ELEMENT_HPP
#define SBROWSER2_SVG_ELEMENT_HPP

#include "dom/nodes/element.hpp"
namespace svg::elements {class svg_element;}

namespace svg::elements {class svg_svg_element;}
namespace svg::attribute_types {class svg_animated_string;}


class svg::elements::svg_element
        : public dom::nodes::element
        , svg::mixins::svg_element_instance
        , html::mixins::html_or_svg_element
{
public constructors:
    DOM_CTORS(svg_element);
    svg_element() = default;

public js_properties:
    ext::property<attribute_types::svg_animated_string> class_name;
    ext::property<svg_svg_element*> owner_svg_element;
    ext::property<svg_element*> viewport_element;

private cpp_accessors:
    DEFINE_GETTER(owner_svg_element);
    DEFINE_GETTER(viewport_element);
};


#endif //SBROWSER2_SVG_ELEMENT_HPP
