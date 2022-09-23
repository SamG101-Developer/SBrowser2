#ifndef SBROWSER2_SVG_ELEMENT_HPP
#define SBROWSER2_SVG_ELEMENT_HPP

#include "dom/nodes/element.hpp"
#include "css/cssom/mixins/element_css_inline_style.hpp"
namespace svg::elements {class svg_element;}

namespace svg::elements {class svg_svg_element;}
namespace svg::types {class svg_animated_string;}


class svg::elements::svg_element
        : public dom::nodes::element
        , public svg::mixins::svg_element_instance
        , public html::mixins::html_or_svg_element
        , public css::cssom::mixins::element_css_inline_style
{
public constructors:
    DOM_CTORS(svg_element);
    svg_element() = default;

private js_properties:
    ext::property<types::svg_animated_string> class_name;
    ext::property<svg_svg_element*> owner_svg_element;
    ext::property<svg_element*> viewport_element;

private js_properties:
    DEFINE_CUSTOM_GETTER(owner_svg_element);
    DEFINE_CUSTOM_GETTER(viewport_element);
};


#endif //SBROWSER2_SVG_ELEMENT_HPP
