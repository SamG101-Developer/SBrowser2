#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_field_set_element;}
namespace html::elements {class html_field_set_element_private;}

#include "ext/ranges.hpp"
namespace html::elements {class html_form_element;}
namespace html::elements {class html_legend_element;}


class html::elements::html_field_set_element
        : public html_element
        , public mixins::validatable
{
public friends:
    friend class html::elements::html_legend_element;

public constructors:
    DOM_CTORS(html_field_set_element);
    MAKE_PIMPL(html_field_set_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(type, ext::string) {return u8"fieldset";}
    DEFINE_GETTER(form, html_form_element*);
    DEFINE_GETTER(elements, ranges::any_helpful_view<html::elements::html_element*>);

    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(name, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_HPP
