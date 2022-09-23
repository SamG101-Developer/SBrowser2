#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_COL_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_COL_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_col_element;}


class html::elements::html_table_col_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_col_element);
    html_table_col_element();

private js_properties:
    ext::property<ext::number<ulong>> span;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_COL_ELEMENT_HPP
