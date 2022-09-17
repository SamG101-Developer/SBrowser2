#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_label_element;}

namespace html::elements {class html_form_element;}


class html::elements::html_label_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_label_element);
    html_label_element() = default;

public js_properties:
    ext::property<html_form_element*> form;
    ext::property<html_element*> control;
    ext::property<ext::string> html_for;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(form);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LABEL_ELEMENT_HPP
