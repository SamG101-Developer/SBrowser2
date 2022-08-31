#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_LIST_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_LIST_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_data_list_element;}


class html::elements::html_data_list_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_data_list_element);
    html_data_list_element();

public js_properties:
    ext::property<std::unique_ptr<ext::vector<html_element*>>> options;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DATA_LIST_ELEMENT_HPP
