module;
#include "ext/macros/macros.hpp"


export module apis.html.html_element_private;
import apis.dom.element_private;
import apis.html.mixins.content_editable_private;
import apis.html.mixins.html_or_svg_element_private;

import apis.html.types;
import ext.core;


DEFINE_PRIVATE_CLASS(html, html_element)
        : dom::element_private
        , html::content_editable_private
        , html::html_or_svg_element_private
        // , css::cssom::mixins::element_css_inline_style_private TODO
{
public:
    MAKE_QIMPL(html_element);

public:
    ext::string title;
    ext::string lang;
    ext::boolean translate_mode;
    detail::directionality_t dir;
    ext::string access_key;

    ext::boolean attached_internals;
};
