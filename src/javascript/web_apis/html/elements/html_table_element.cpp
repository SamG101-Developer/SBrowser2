#include "html_table_element.hpp"
#include "html_table_element_private.hpp"

#include "ext/ranges.hpp"
#include <range/v3/to_container.hpp>


auto html::elements::html_table_element::get_caption() const -> html_table_caption_element*
{
    ACCESS_PIMPL(const html_table_element);
    decltype(auto) caption_children = d->child_nodes
            | ranges::views::transform([](auto&& manager) {return manager.get();})
            | ranges::views::cast<html_table_caption_element*>;

    return caption_children.empty() ? nullptr : caption_children.front();
}


auto html::elements::html_table_element::set_caption(
        html::elements::html_table_caption_element* new_caption)
        -> html_table_caption_element*
{
    ACCESS_PIMPL(html_table_element);
    decltype(auto) caption_children = d->child_nodes
            | ranges::views::underlying()
            | ranges::views::cast<html_table_caption_element*>;
    caption_children[0] = new_caption;

    auto m = ext::string{};
    auto n = m
            | ranges::views::lowercase
            | ranges::to<ext::string>();
}

