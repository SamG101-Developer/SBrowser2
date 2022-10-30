#ifndef SBROWSER2_HTML_ELEMENT_HPP
#define SBROWSER2_HTML_ELEMENT_HPP

#include "dom/nodes/element.hpp"
#include "html/mixins/content_editable.hpp"
#include "html/mixins/html_or_svg_element.hpp"
#include "css/cssom/mixins/element_css_inline_style.hpp"
namespace html::elements {class html_element;}
namespace html::elements {class html_element_private;}


#include INCLUDE_INNER_TYPES(html)
namespace html::other {class element_internals;}


class html::elements::html_element
        : public dom::nodes::element
        , public mixins::content_editable
        , public mixins::html_or_svg_element
        , public css::cssom::mixins::element_css_inline_style
{
public constructors:
    DOM_CTORS(html_element);
    MAKE_PIMPL(html_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto click() -> void;
    auto attach_internals() -> other::element_internals;

private js_properties:
    DEFINE_GETTER(title, ext::string_view);
    DEFINE_GETTER(lang, ext::string_view);
    DEFINE_GETTER(translate, ext::boolean);
    DEFINE_GETTER(dir, detail::directionality_t);
    DEFINE_GETTER(access_key_label, ext::string);
    DEFINE_GETTER(access_key, ext::string_view);
    DEFINE_GETTER(autocapitalize, detail::autocapitalize_hint_t);
    DEFINE_GETTER(inner_text, ext::string);
    DEFINE_GETTER(outer_text, ext::string);
    DEFINE_GETTER(hidden, ext::boolean);
    DEFINE_GETTER(inert, ext::boolean);
    DEFINE_GETTER(draggable, ext::boolean);
    DEFINE_GETTER(spellcheck, ext::bool_string_t);

    DEFINE_SETTER(title, ext::string);
    DEFINE_SETTER(lang, ext::string);
    DEFINE_SETTER(translate, ext::boolean);
    DEFINE_SETTER(dir, detail::directionality_t);
    DEFINE_SETTER(access_key, ext::string);
    DEFINE_SETTER(autocapitalize, detail::autocapitalize_hint_t);
    DEFINE_SETTER(inner_text, ext::string);
    DEFINE_SETTER(outer_text, ext::string);
    DEFINE_SETTER(hidden, ext::boolean);
    DEFINE_SETTER(inert, ext::boolean);
    DEFINE_SETTER(draggable, ext::boolean);
    DEFINE_SETTER(spellcheck, ext::bool_string_t);

};


#endif //SBROWSER2_HTML_ELEMENT_HPP
