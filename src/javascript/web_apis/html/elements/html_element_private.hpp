#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"

#include "html/mixins/content_editable_private.hpp"
#include "html/mixins/html_or_svg_element_private.hpp"
// #include "css/cssom/mixins/element_css_inline_style_private.hpp"

#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(html::elements, html_element)
        : dom::nodes::element_private
        , mixins::content_editable_private
        , mixins::html_or_svg_element_private
        // , css::cssom::mixins::element_css_inline_style_private TODO
{
    ext::string title;
    ext::string lang;
    ext::boolean translate_mode;
    detail::directionality_t dir;
    ext::string access_key;

    ext::boolean attached_internals;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_ELEMENT_PRIVATE_HPP
