#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_template_element;}

namespace dom::nodes {class document_fragment;}


class html::elements::html_template_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_template_element);
    html_template_element();

private js_properties:
    ext::property<std::unique_ptr<dom::nodes::document_fragment>> content;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEMPLATE_ELEMENT_HPP
