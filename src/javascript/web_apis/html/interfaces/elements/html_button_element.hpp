#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_button_element;}
namespace html::elements {class html_button_element_private;}

#include INCLUDE_INNER_TYPES(html)
#include "ext/span.hpp"
namespace html::elements {class html_form_element;}


class html::elements::html_button_element
        : public html_element
        , public mixins::validatable
{
public constructors:
    DOM_CTORS(html_button_element);
    MAKE_PIMPL(html_button_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(form, html_form_element*);
    DEFINE_GETTER(labels, ext::vector_span<dom::nodes::node*>);
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(form_action, ext::string_view);
    DEFINE_GETTER(form_enctype, detail::form_enctype_t);
    DEFINE_GETTER(form_method, detail::form_method_t);
    DEFINE_GETTER(form_no_validate, ext::boolean);
    DEFINE_GETTER(form_target, ext::string_view);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(type, detail::button_state_t);
    DEFINE_GETTER(value, ext::string_view);

    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(form_action, ext::string);
    DEFINE_SETTER(form_enctype, detail::form_enctype_t);
    DEFINE_SETTER(form_method, detail::form_method_t);
    DEFINE_SETTER(form_no_validate, ext::boolean);
    DEFINE_SETTER(form_target, ext::string);
    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(type, detail::button_state_t);
    DEFINE_SETTER(value, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_BUTTON_ELEMENT_HPP
