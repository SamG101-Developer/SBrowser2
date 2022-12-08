#ifndef SBROWSER2_SVG_ELEMENT_HPP
#define SBROWSER2_SVG_ELEMENT_HPP


//#include "svg/mixins/svg_element_instance.hpp"
#include "html/mixins/html_or_svg_element.hpp"
#include "css/cssom/mixins/element_css_inline_style.hpp"
namespace svg::elements {class svg_element;}
namespace svg::elements {class svg_element_private;}

namespace svg::elements {class svg_svg_element;}
namespace svg::types {class svg_animated_string;}


class svg::elements::svg_element
        : public dom::nodes::element
//        , public svg::mixins::svg_element_instance
        , public html::mixins::html_or_svg_element
        , public css::cssom::mixins::element_css_inline_style
{
public constructors:
    DOM_CTORS(svg_element);
    MAKE_PIMPL(svg_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(class_name, types::svg_animated_string*);
    DEFINE_GETTER(owner_svg_element, svg_svg_element*);
    DEFINE_GETTER(viewport_element, svg_element*);
};


#endif //SBROWSER2_SVG_ELEMENT_HPP
