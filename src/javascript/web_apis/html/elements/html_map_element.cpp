#include "html_map_element.hpp"
#include "html_map_element_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "html/elements/html_area_element.hpp"


auto html::elements::html_map_element::get_name() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_map_element);
        return d->name;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_map_element::get_areas() const -> ranges::any_helpful_view<dom::nodes::element*>
{
    ACCESS_PIMPL(const html_map_element);
    return dom::detail::descendants(this) | ranges::views::cast_all_to<html_area_element*>();
}


auto html::elements::html_map_element::set_name(ext::string new_name) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_map_element);
        return d->name = std::move(new_name);
    CE_REACTIONS_METHOD_EXE
}
