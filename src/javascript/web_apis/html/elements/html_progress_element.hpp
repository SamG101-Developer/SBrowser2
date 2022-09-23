#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PROGRESS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PROGRESS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_progress_element;}


class html::elements::html_progress_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_progress_element);
    html_progress_element() = default;

private js_properties:
    ext::property<ext::number<double>> value;
    ext::property<ext::number<double>> max;
    ext::property<ext::number<double>> position;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>> labels;

private js_properties:
    DEFINE_CUSTOM_GETTER(value);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_PROGRESS_ELEMENT_HPP
