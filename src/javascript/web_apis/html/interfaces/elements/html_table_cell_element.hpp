#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_cell_element;}
namespace html::elements {class html_table_cell_element_private;}

#include INCLUDE_INNER_TYPES(html)


class html::elements::html_table_cell_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_cell_element);
    MAKE_PIMPL(html_table_cell_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    DEFINE_GETTER(col_span, ext::number<ulong>);
    DEFINE_GETTER(row_span, ext::number<ulong>);
    DEFINE_GETTER(cell_index, ext::number<long>);
    DEFINE_GETTER(headers, ext::string_view);
    DEFINE_GETTER(scope, detail::table_cell_scope_t);
    DEFINE_GETTER(abbr, ext::string_view);

    DEFINE_SETTER(col_span, ext::number<ulong>);
    DEFINE_SETTER(row_span, ext::number<ulong>);
    DEFINE_SETTER(headers, ext::string);
    DEFINE_SETTER(scope, detail::table_cell_scope_t);
    DEFINE_SETTER(abbr, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_HPP
