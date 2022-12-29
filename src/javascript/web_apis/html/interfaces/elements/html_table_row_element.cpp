#include "html_table_row_element.hpp"
#include "html_table_row_element_private.hpp"








#include "html/elements/html_table_cell_element.hpp"
#include "html/elements/html_table_cell_element_private.hpp"
#include "html/elements/html_table_element.hpp"
#include "html/elements/html_table_element_private.hpp"
#include "html/elements/html_table_section_element.hpp"
#include "html/elements/html_table_section_element_private.hpp"


auto html::elements::html_table_row_element::insert_cell(ext::number<long> index) -> html_table_cell_element*
{
    ACCESS_PIMPL(html_table_row_element);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [d, index] {return index < -1 || index > d->t_cells.size();},
            u8"Cell index must be -1 <= N <= cells.length()");

    decltype(auto) table_cell = dom::detail::create_an_element(d->node_document.get(), u8"td", d->namespace_);
}


auto html::elements::html_table_row_element::get_row_index() const -> ext::number<long>
{
    ACCESS_PIMPL(const html_table_row_element);
    if (decltype(auto) cast_parent = dom_cast<html_table_element*>(d->parent_node.get()))
        return ranges::index_of(cast_parent->d_func()->table_children<html_table_row_element>(), this);

    if (decltype(auto) cast_grandparent = dom_cast<html_table_element*>(d->parent_node->d_func()->parent_node.get()))
        return ranges::index_of(cast_grandparent->d_func()->table_children<html_table_row_element>(), this);

    return -1;
}


auto html::elements::html_table_row_element::get_section_row_index() const -> ext::number<long>
{
    ACCESS_PIMPL(const html_table_row_element);
    using table_like_t = ext::variant<html_table_element*, html_table_section_element*>;
    decltype(auto) cast_parent = ext::variant_cast<table_like_t>(d->parent_node.get());
    decltype(auto) parent_rows = ext::visit([](auto* parent) {return parent->d_func()->t_rows;}, cast_parent);
    return ranges::index_of(parent_rows, this);
}


auto html::elements::html_table_row_element::get_cells() const -> ranges::any_helpful_view<html_table_cell_element*>
{
    ACCESS_PIMPL(const html_table_row_element);
    return d->t_cells;
}
