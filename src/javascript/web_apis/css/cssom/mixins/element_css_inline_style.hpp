#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_ELEMENT_CSS_INLINE_STYLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_ELEMENT_CSS_INLINE_STYLE_HPP


namespace css::cssom::mixins {class element_css_inline_style;}
namespace css::cssom::mixins {class element_css_inline_style_private;}

namespace css::cssom::other {class css_style_declaration;}


class css::cssom::mixins::element_css_inline_style
        : public virtual dom_object
{
public constructors:
    element_css_inline_style() = default;
    MAKE_PIMPL(element_css_inline_style);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(style, other::css_style_declaration*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_ELEMENT_CSS_INLINE_STYLE_HPP
