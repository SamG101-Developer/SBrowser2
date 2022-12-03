#pragma once
#include "html/mixins/html_or_svg_element.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/element_private.hpp"
#include "html/mixins/html_or_svg_element_private.hpp"
#include "css/cssom/mixins/element_css_inline_style_private.hpp"

namespace svg::types {class svg_animated_string;}


DEFINE_PRIVATE_CLASS(svg::elements, svg_element)
        : dom::nodes::element_private
        , html::mixins::html_or_svg_element_private
        , css::cssom::mixins::element_css_inline_style_private
{
    std::unique_ptr<types::svg_animated_string> class_;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SVG_ELEMENTS_SVG_ELEMENT_PRIVATE_HPP
