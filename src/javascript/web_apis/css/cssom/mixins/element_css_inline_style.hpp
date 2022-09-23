#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_ELEMENT_CSS_INLINE_STYLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_ELEMENT_CSS_INLINE_STYLE_HPP

#include "dom_object.hpp"
namespace css::cssom::mixins {class element_css_inline_style;}

namespace css::cssom::other {class css_style_declaration;}


class css::cssom::mixins::element_css_inline_style
        : public virtual dom_object
{
private js_properties:
    ext::property<std::unique_ptr<other::css_style_declaration>> style;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_ELEMENT_CSS_INLINE_STYLE_HPP
