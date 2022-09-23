#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DETAILS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DETAILS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_details_element;}


class html::elements::html_details_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_details_element);
    html_details_element() = default;

private js_properties:
    ext::property<ext::boolean> open;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_DETAILS_ELEMENT_HPP
