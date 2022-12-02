#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TABLE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TABLE_INTERNALS_HPP

#include "ext/number.ixx"
#include "ext/pair.ixx"
namespace html::elements {class html_table_element;}
namespace html::elements {class html_table_cell_element;}
namespace html::elements {class html_table_row_element;}
namespace html::elements {class html_table_section_element;}


namespace html::detail
{
    auto determine_if_any_table_model_errors(
            elements::html_table_element* element)
            -> elements::html_table_element*;

    auto process_row_groups(
            elements::html_table_section_element* element)
            -> void;

    auto end_row_group()
            -> void;

    auto process_rows(
            elements::html_table_row_element* element)
            -> void;

    auto assign_header_cells(
            elements::html_table_cell_element* principal_cell)
            -> void;

    auto scan_and_assign_header_cells(
            elements::html_table_cell_element* principal_cell,
            /* TODO : header-list */
            ext::pair<ext::number<int>, ext::number<int>>&& initial,
            ext::number<int> delta_x,
            ext::number<int> delta_y)
            -> void;

    auto is_column_header(
            elements::html_table_cell_element* cell,
            ext::pair<ext::number<int>, ext::number<int>>&& coordinates,
            ext::number<int> width,
            ext::number<int> height)
            -> ext::boolean;

    auto is_row_header(
            elements::html_table_cell_element* cell,
            ext::pair<ext::number<int>, ext::number<int>>&& coordinates,
            ext::number<int> width,
            ext::number<int> height)
            -> ext::boolean;

    auto is_column_group_header(
            elements::html_table_cell_element* cell)
            -> ext::boolean;

    auto is_row_group_header(
            elements::html_table_cell_element* cell)
            -> ext::boolean;

    auto is_empty_cell(
            elements::html_table_cell_element* cell)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TABLE_INTERNALS_HPP
