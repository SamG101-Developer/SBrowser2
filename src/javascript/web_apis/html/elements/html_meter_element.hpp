#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_meter_element;}


class html::elements::html_meter_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_meter_element);
    html_meter_element() = default;

public js_properties:
    ext::property<ext::number<double>> value;
    ext::property<ext::number<double>> min;
    ext::property<ext::number<double>> max;
    ext::property<ext::number<double>> low;
    ext::property<ext::number<double>> high;
    ext::property<ext::number<double>> optimum;

    ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>> labels;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_METER_ELEMENT_HPP
