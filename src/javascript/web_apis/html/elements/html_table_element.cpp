#include "html_table_element.hpp"
#include "html_table_element_private.hpp"

#include "ext/ranges.hpp"

#include "dom/detail/mutation_internals.hpp"

#include "html/detail/html_element_internals.hpp"
#include "html/elements/html_table_caption_element.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/view/take.hpp>


auto html::elements::html_table_element::create_caption() -> html_table_caption_element*
{
    ACCESS_PIMPL(html_table_element);

    decltype(auto) caption_children = d->table_children<html_table_caption_element>();
    return_if (!caption_children.empty()) caption_children.front();

    decltype(auto) new_caption = detail::table_create<html_table_caption_element>(u8"caption", d->node_document.get());
    dom::detail::insert(std::move(new_caption), this, d->child_nodes.front().get());
    return dom_cast<html_table_caption_element*>(d->child_nodes[0].get());
}


auto html::elements::html_table_element::delete_caption() -> html_table_caption_element*
{
    ACCESS_PIMPL(html_table_element);
    dom::detail::remove(ranges::front(d->child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::cast<html_table_caption_element*>));
}


auto html::elements::html_table_element::get_caption() const -> html_table_caption_element*
{
    ACCESS_PIMPL(const html_table_element);
    decltype(auto) caption_children = d->table_children<html_table_caption_element>();
    return caption_children.empty() ? nullptr : caption_children.front();
}


auto html::elements::html_table_element::set_caption(
        std::unique_ptr<html_table_caption_element>&& new_caption)
        -> std::unique_ptr<html_table_caption_element>&&
{
    ACCESS_PIMPL(html_table_element);
    delete_caption();
    return dom::detail::insert(std::move(new_caption), this, d->child_nodes.front().get());
}

