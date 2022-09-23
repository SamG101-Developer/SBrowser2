#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MAP_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MAP_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_map_element;}


class html::elements::html_map_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_map_element);
    html_map_element();

private js_properties:
    ext::property<ext::string> name;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::element*>>> areas;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_MAP_ELEMENT_HPP
