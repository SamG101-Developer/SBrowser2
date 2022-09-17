#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_field_set_element;}

namespace html::elements {class html_form_element;}


class html::elements::html_field_set_element
        : public html_element
        , public mixins::validatable
{
public constructors:
    DOM_CTORS(html_field_set_element);
    html_field_set_element() = default;

public js_properties:
    ext::property<ext::boolean> disabled;
    ext::property<ext::string> name;
    ext::property<ext::string> type;
    ext::property<html_form_element*> form;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(type) {return "fieldset";}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FIELD_SET_ELEMENT_HPP
