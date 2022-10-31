#include "html_table_cell_element.hpp"
#include "html_table_cell_element_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "html/elements/html_table_row_element.hpp"
#include "html/elements/html_table_row_element_private.hpp"


auto html::elements::html_table_cell_element::get_col_span() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_table_cell_element);
        return d->col_span;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::get_row_span() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_table_cell_element);
        return d->row_span;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::get_headers() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_table_cell_element);
        return d->headers;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::get_cell_index() const -> ext::number<long>
{
    ACCESS_PIMPL(const html_table_cell_element);
    decltype(auto) cast_parent = dynamic_cast<html_table_row_element*>(d->parent_node.get());
    return ranges::index_of(cast_parent->d_func()->t_cells, this);
}


auto html::elements::html_table_cell_element::get_scope() const -> detail::table_cell_scope_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_table_cell_element);
        return d->scope;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::get_abbr() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_table_cell_element);
        return d->abbr;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::set_col_span(ext::number<ulong> new_col_span) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_table_cell_element);
        return d->col_span = new_col_span;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::set_row_span(ext::number<ulong> new_row_span) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_table_cell_element);
        return d->row_span = new_row_span;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::set_headers(ext::string new_headers) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_table_cell_element);
        return d->headers = std::move(new_headers);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::set_scope(detail::table_cell_scope_t new_scope) -> detail::table_cell_scope_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_table_cell_element);
        return d->scope = new_scope;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_table_cell_element::set_abbr(ext::string new_abbr) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_table_cell_element);
        return d->abbr = std::move(new_abbr);
    CE_REACTIONS_METHOD_EXE
}
