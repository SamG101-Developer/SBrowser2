#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_output_element;}

namespace html::elements {class html_form_element;}


class html::elements::html_output_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_output_element);
    html_output_element() = default;

public js_properties:
    ext::property<ext::string> html_for;
    ext::property<ext::string> name;
    ext::property<ext::string> type;
    ext::property<ext::string> default_value;
    ext::property<ext::string> value;
    ext::property<html_form_element*> form;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>> labels;

private cpp_properties:
    ext::string m_default_value_override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(default_value);

    DEFINE_CUSTOM_GETTER(type) {return "output";}
    DEFINE_CUSTOM_SETTER(default_value);
    DEFINE_CUSTOM_SETTER(value);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_OUTPUT_ELEMENT_HPP
