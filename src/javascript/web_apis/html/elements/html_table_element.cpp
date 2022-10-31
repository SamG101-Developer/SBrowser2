#include "html_table_element.hpp"
#include "dom/_typedefs.hpp"
#include "html_table_element_private.hpp"

#include "ext/ranges.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"

#include "html/detail/html_element_internals.hpp"
#include "html/elements/html_table_caption_element.hpp"
#include "html/elements/html_table_section_element.hpp"
#include "html/elements/html_table_section_element_private.hpp"
#include "html/elements/html_table_col_element.hpp"
#include "html/elements/html_table_row_element.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/view/take.hpp>


auto html::elements::html_table_element::create_caption() -> html_table_caption_element*
{
    ACCESS_PIMPL(html_table_element);

    // If there are any HTMLTableCaptionElement elements that already exist, return the first one from the table's
    // 'child_nodes'. Cast it down to the correct type and return it.
    if (!d->t_captions.empty())
        return d->t_captions.front();

    // Otherwise, create a new HTMLTableCaptionElement and insert it into this HTMLTableElement before the first
    // HTMLTableCaptionElement child of this HTMLTableElement. Return the new HTMLTableCaptionElement.
    decltype(auto) children = d->child_nodes | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get);
    decltype(auto) new_caption = detail::table_create<html_table_caption_element>(u8"caption", d->node_document.get());
    decltype(auto) inserted = dom::detail::insert(std::move(new_caption), this, children.front());
    return dom_cast<html_table_caption_element*>(inserted);
}


auto html::elements::html_table_element::create_t_head() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);

    // If there are any HTMLTableSectionElement(local_name="thead") elements that already exist, return the first one
    // from the table's 'table_children()'. Cast it down to the correct type and return it.
    if (!d->t_heads.empty())
        return d->t_heads.front();

    // Otherwise, create a new HTMLTableSectionElement(local_name="thead") and insert it into this HTMLTableElement
    // before the first [HTMLTableCaptionElement | HTMLTableColElement] child of this HTMLTableElement. Return the new
    // HTMLTableSectionElement(local_name="thead).
    decltype(auto) children = d->table_children<html_table_caption_element, html_table_col_element>();
    decltype(auto) new_t_head = detail::table_create<html_table_section_element>(u8"thead", d->node_document.get());
    decltype(auto) inserted = dom::detail::insert(std::move(new_t_head), this, children.front());
    return dom_cast<html_table_section_element*>(inserted);
}


auto html::elements::html_table_element::create_t_foot() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);

    // If there are any HTMLTableSectionElement(local_name="tfoot") elements that already exist, return the first one
    // from the table's 'table_children()'. Cast it down to the correct type and return it.
    if (!d->t_footers.empty())
        return d->t_footers.front();

    // Otherwise, create a new HTMLTableSectionElement(local_name="tfoot") and insert it into this HTMLTableElement
    // after the last Node child of this HTMLTableElement. Return the new HTMLTableSectionElement(local_name="tfoot").
    decltype(auto) new_t_foot = detail::table_create<html_table_section_element>(u8"thead", d->node_document.get());
    decltype(auto) inserted = dom::detail::append(std::move(new_t_foot), this);
    return dom_cast<html_table_section_element*>(inserted);
}


auto html::elements::html_table_element::create_t_body() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);

    // Create a new HTMLTableSectionElement(local_name="tbody") and insert it into this HTMLTableElement after the last
    // HTMLTableSectionElement(local_name="tbody"). Return the new HTMLTableSectionElement(local_name="tbody").
    decltype(auto) new_t_body = detail::table_create<html_table_section_element>(u8"tbody", d->node_document.get());
    decltype(auto) inserted = dom::detail::insert(std::move(new_t_body), this, d->t_bodies.back()); // TODO : insert AFTER not BEFORE
    return dom_cast<html_table_section_element*>(inserted);
}


auto html::elements::html_table_element::insert_row(ext::number<long> index) -> html_table_row_element*
{
    ACCESS_PIMPL(html_table_element);

    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [index, d] {return index < -1 || index > d->t_rows.size();},
            u8"Index must -1 <= N <= rows.length()");

    if (d->t_rows.empty() && d->t_bodies.empty())
    {
        decltype(auto) new_body = detail::table_create<html_table_section_element>(u8"tbody", d->node_document.get());
        decltype(auto) new_row  = detail::table_create<html_table_row_element>(u8"row", d->node_document.get());
        dom::detail::append(std::move(new_row), new_body);
        dom::detail::append(std::move(new_body), this);
        return d->t_rows.back();
    }

    if (d->t_rows.empty())
    {
        decltype(auto) new_row = detail::table_create<html_table_row_element>(u8"row", d->node_document.get());
        return dom::detail::append(std::move(new_row), d->t_bodies.back());
    }

    decltype(auto) new_row = detail::table_create<html_table_row_element>(u8"row", d->node_document.get());
    return index == -1 || index == d->t_rows.size()
            ? dom::detail::append(std::move(new_row), d->t_rows.back()->d_func()->parent_node.get())
            : dom::detail::insert(std::move(new_row), d->t_rows.at(index));
}


auto html::elements::html_table_element::delete_caption() -> html_table_caption_element*
{
    ACCESS_PIMPL(html_table_element);
    dom::detail::remove(ranges::front(d->child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_caption_element*>));
}


auto html::elements::html_table_element::delete_t_head() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);
    dom::detail::remove(ranges::front(d->t_heads));
}


auto html::elements::html_table_element::delete_t_foot() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);
    dom::detail::remove(ranges::front(d->t_footers));
}


auto html::elements::html_table_element::delete_row(ext::number<long> index) -> html_table_row_element*
{
    ACCESS_PIMPL(html_table_element);

    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [d, index] {return index < -1 || index >= d->t_rows.size();},
            u8"Index must -1 <= N < rows.length()");

    d->child_nodes
            |= ranges::actions::transform(&std::unique_ptr<dom::nodes::node>::get)
            |  ranges::actions::remove_at_index(index % d->t_rows.size());
}


auto html::elements::html_table_element::get_caption() const -> html_table_caption_element*
{
    ACCESS_PIMPL(const html_table_element);
    return d->t_captions.empty() ? nullptr : d->t_captions.front();
}


auto html::elements::html_table_element::get_t_head() const -> html_table_section_element*
{
    ACCESS_PIMPL(const html_table_element);
    return d->t_heads.empty() ? nullptr : d->t_heads.front();
}


auto html::elements::html_table_element::get_t_foot() const -> html_table_section_element*
{
    ACCESS_PIMPL(const html_table_element);
    return d->t_footers.empty() ? nullptr : d->t_footers.front();
}


auto html::elements::html_table_element::get_t_bodies() const -> ranges::any_helpful_view<html_table_section_element*>
{
    ACCESS_PIMPL(const html_table_element);
    return d->t_bodies;
}


auto html::elements::html_table_element::get_rows() const -> ranges::any_helpful_view<html_table_row_element*>
{
    ACCESS_PIMPL(const html_table_element);
    return d->t_rows;
}


auto html::elements::html_table_element::set_caption(
        std::unique_ptr<html_table_caption_element>&& new_caption)
        -> std::unique_ptr<html_table_caption_element>&&
{
    ACCESS_PIMPL(html_table_element);
    delete_caption();
    return dom::detail::insert(std::move(new_caption), this, d->child_nodes.front().get());
}


auto html::elements::html_table_element::set_t_head(
        std::unique_ptr<html_table_section_element>&& new_t_head)
        -> std::unique_ptr<html_table_section_element>&&
{
    ACCESS_PIMPL(html_table_element);
    delete_t_head();
    return dom::detail::insert(std::move(new_t_head), this, d->table_children<html_table_section_element, html_table_col_element>().front());
}


auto html::elements::html_table_element::set_t_foot(
        std::unique_ptr<html_table_section_element>&& new_t_foot)
        -> std::unique_ptr<html_table_section_element>&&
{
    ACCESS_PIMPL(html_table_element);
    delete_t_foot();
    return dom::detail::append(std::move(new_t_foot), this);
}

