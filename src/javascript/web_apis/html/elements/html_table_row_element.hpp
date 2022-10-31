#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_row_element;}
namespace html::elements {class html_table_row_element_private;}

#include "ext/ranges.hpp"
namespace html::elements {class html_table_cell_element;}


class html::elements::html_table_row_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_row_element);
    MAKE_PIMPL(html_table_row_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto insert_cell(ext::number<long> index = -1) -> html_table_cell_element*;
    auto delete_cell(ext::number<long> index = -1) -> html_table_cell_element*;

private js_properties:
    DEFINE_GETTER(cells, ranges::any_helpful_view<html_table_cell_element*>);
    DEFINE_GETTER(row_index, ext::number<long>);
    DEFINE_GETTER(section_row_index, ext::number<long>);
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_HPP
