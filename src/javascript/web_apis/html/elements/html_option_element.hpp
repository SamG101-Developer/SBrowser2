#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_option_element;}

namespace html::elements {class html_form_element;}


class html::elements::html_option_element
         : public html_element
{
public constructors:
    DOM_CTORS(html_option_element);
    html_option_element();

public js_properties:
    ext::property<ext::boolean> disabled;
    ext::property<html_form_element*> form;
    ext::property<ext::string> label;
    ext::property<ext::boolean> default_selected;
    ext::property<ext::boolean> selected;
    ext::property<ext::string> value;
    ext::property<ext::string> text;
    ext::property<ext::number<long>> index;

private cpp_accessors:
    DEFINE_GETTER(index);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OPTION_ELEMENT_HPP
