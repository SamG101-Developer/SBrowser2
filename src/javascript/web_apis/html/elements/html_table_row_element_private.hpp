#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_table_row_element) : html::elements::html_element_private
{
    ranges::any_helpful_view<html_table_cell_element*> t_cells = child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_cell_element*>;
            // | ranges::views::filter_eq(&html_table_cell_element_private::local_name, u8"cell", ext::get_pimpl);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ROW_ELEMENT_PRIVATE_HPP
