#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_cell_element;}

#include INCLUDE_INNER_TYPES(html)


class html::elements::html_table_cell_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_cell_element);
    html_table_cell_element();

public js_methods:
    ext::property<ext::number<ulong>> col_span;
    ext::property<ext::number<ulong>> row_span;
    ext::property<ext::number<long>> cell_index;
    ext::property<ext::string> headers;

    ext::property<detail::table_cell_scope_t> scope;
    ext::property<ext::string> abbr;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_HPP
