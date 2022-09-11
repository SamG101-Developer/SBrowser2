#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_table_row_element;}

namespace html::elements {class html_table_cell_element;}


class html::elements::html_table_row_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_table_row_element);
    html_table_row_element();

public js_methods:
    auto insert_cell(ext::number<long> index = -1) -> html_table_cell_element;
    auto delete_cell(ext::number<long> index = -1) -> html_table_cell_element*;

public js_properties:
    ext::property<std::unique_ptr<ext::vector<html_table_cell_element*>>> cells;
    ext::property<ext::number<long>> row_index;
    ext::property<ext::number<long>> section_row_index;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_HPP
