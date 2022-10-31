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
    decltype(auto) caption_children = d->table_children<html_table_caption_element>();
    if (!caption_children.empty())
        return caption_children.front();

    // Otherwise, create a new HTMLTableCaptionElement and insert it into this HTMLTableElement before the first
    // HTMLTableCaptionElement child of this HTMLTableElement. Return the new HTMLTableCaptionElement.
    decltype(auto) children = d->child_nodes | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get);
    decltype(auto) new_caption = detail::table_create<html_table_caption_element>(u8"caption", d->node_document.get());
    return dom::detail::insert(std::move(new_caption), this, children.front());
}


auto html::elements::html_table_element::create_t_head() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);

    // If there are any HTMLTableSectionElement(local_name="thead") elements that already exist, return the first one
    // from the table's 'table_children()'. Cast it down to the correct type and return it.
    decltype(auto) t_head_children = d->table_children<html_table_section_element>(u8"thead");
    if (!t_head_children.empty())
        return t_head_children.front();

    // Otherwise, create a new HTMLTableSectionElement(local_name="thead") and insert it into this HTMLTableElement
    // before the first [HTMLTableCaptionElement | HTMLTableColElement] child of this HTMLTableElement. Return the new
    // HTMLTableSectionElement(local_name="thead).
    decltype(auto) children = d->table_children<html_table_caption_element, html_table_col_element>();
    decltype(auto) new_t_head = detail::table_create<html_table_section_element>(u8"thead", d->node_document.get());
    return dom::detail::insert(std::move(new_t_head), this, children.front());
}


auto html::elements::html_table_element::create_t_foot() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);

    // If there are any HTMLTableSectionElement(local_name="tfoot") elements that already exist, return the first one
    // from the table's 'table_children()'. Cast it down to the correct type and return it.
    decltype(auto) t_foot_children = d->table_children<html_table_section_element>(u8"tfoot");
    if (!t_foot_children.empty())
        return t_foot_children.front();

    // Otherwise, create a new HTMLTableSectionElement(local_name="tfoot") and insert it into this HTMLTableElement
    // after the last Node child of this HTMLTableElement. Return the new HTMLTableSectionElement(local_name="tfoot").
    decltype(auto) new_t_foot = detail::table_create<html_table_section_element>(u8"thead", d->node_document.get());
    return dom::detail::append(std::move(new_t_foot), this);
}


auto html::elements::html_table_element::create_t_body() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);

    // Create a new HTMLTableSectionElement(local_name="tbody") and insert it into this HTMLTableElement after the last
    // HTMLTableSectionElement(local_name="tbody"). Return the new HTMLTableSectionElement(local_name="tbody").
    decltype(auto) children = d->table_children<html_table_caption_element>(u8"tbody");
    decltype(auto) new_t_body = detail::table_create<html_table_section_element>(u8"tbody", d->node_document.get());
    return dom::detail::insert(std::move(new_t_body), this, children.back()); // TODO : insert AFTER not BEFORE
}


auto html::elements::html_table_element::insert_row(ext::number<long> index) -> html_table_row_element*
{
    ACCESS_PIMPL(html_table_element);

    decltype(auto) rows = d->table_children<html_table_row_element>(u8"tr");
    decltype(auto) bodies = d->table_children<html_table_section_element>(u8"tbody");

    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [index, &rows] {return index < -1 || index > rows.size();},
            u8"Index must -1 <= N <= rows.length()");

    if (rows.empty() && bodies.empty())
    {
        decltype(auto) new_body = detail::table_create<html_table_section_element>(u8"tbody", d->node_document.get());
        decltype(auto) new_row  = detail::table_create<html_table_row_element>(u8"row", d->node_document.get());
        dom::detail::append(std::move(new_row), new_body);
        dom::detail::append(std::move(new_body), this);
        return rows.back();
    }

    if (rows.empty())
    {
        decltype(auto) new_row = detail::table_create<html_table_row_element>(u8"row", d->node_document.get());
        return dom::detail::append(std::move(new_row), bodies.back());
    }

    decltype(auto) new_row = detail::table_create<html_table_row_element>(u8"row", d->node_document.get());
    return index == -1 || index == rows.size()
            ? dom::detail::append(std::move(new_row), rows.back()->d_func()->parent_node.get())
            : dom::detail::insert(std::move(new_row), rows.at(index));
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
    dom::detail::remove(ranges::front(d->table_children<html_table_section_element>(u8"thead")));
}


auto html::elements::html_table_element::delete_t_foot() -> html_table_section_element*
{
    ACCESS_PIMPL(html_table_element);
    dom::detail::remove(ranges::front(d->table_children<html_table_section_element>(u8"tfoot")));
}


auto html::elements::html_table_element::delete_row(ext::number<long> index) -> html_table_row_element*
{
    ACCESS_PIMPL(html_table_element);
    decltype(auto) rows = d->table_children<html_table_row_element>(u8"tr");

    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [index, &rows] {return index < -1 || index >= rows.size();},
            u8"Index must -1 <= N < rows.length()");

    d->child_nodes
            |= ranges::actions::transform(&std::unique_ptr<dom::nodes::node>::get)
            |  ranges::actions::remove_at_index(index % rows.size());
}


auto html::elements::html_table_element::get_caption() const -> html_table_caption_element*
{
    ACCESS_PIMPL(const html_table_element);
    decltype(auto) caption_children = d->table_children<html_table_caption_element>();
    return caption_children.empty() ? nullptr : caption_children.front();
}


auto html::elements::html_table_element::get_t_head() const -> html_table_section_element*
{
    ACCESS_PIMPL(const html_table_element);
    decltype(auto) t_head_children = d->table_children<html_table_section_element>(u8"thead");
    return t_head_children.empty() ? nullptr : t_head_children.front();#
}


auto html::elements::html_table_element::get_t_foot() const -> html_table_section_element*
{
    ACCESS_PIMPL(const html_table_element);
    decltype(auto) t_foot_children = d->table_children<html_table_section_element>(u8"tfoot");
    return t_foot_children.empty() ? nullptr : t_foot_children.front();
}


auto html::elements::html_table_element::get_t_bodies() const -> ranges::any_helpful_view<html_table_section_element*>
{
    ACCESS_PIMPL(const html_table_element);
    return d->table_children<html_table_section_element>(u8"tbody");
}


auto html::elements::html_table_element::get_rows() const -> ranges::any_helpful_view<html_table_row_element*>
{
    ACCESS_PIMPL(const html_table_element);
    return d->table_children<html_table_row_element>(u8"tr");
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

