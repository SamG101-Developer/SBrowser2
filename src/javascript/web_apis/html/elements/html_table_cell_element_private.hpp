#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_table_cell_element) : html::elements::html_element_private
{
    ext::number<ulong> col_span;
    ext::number<ulong> row_span;
    ext::string headers;

    detail::table_cell_scope_t scope;
    ext::string abbr;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_CELL_ELEMENT_PRIVATE_HPP
