#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LEGEND_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LEGEND_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_legend_element;}

namespace html::elements {class html_form_element;}


class html::elements::html_legend_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_legend_element);
    html_legend_element() = default;

public js_properties:
    ext::property<html_form_element*> form;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_LEGEND_ELEMENT_HPP
