#include "html_option_element.hpp"
#include "html/_typedefs.hpp"
#include "html_option_element_private.hpp"

#include "ext/casting.ixx"
#include "ext/ranges.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/nodes/text.hpp"
#include "dom/nodes/text_private.hpp"

#include "html/detail/form_controlled_internals.hpp"
#include "html/elements/html_opt_group_element.hpp"
#include "html/elements/html_select_element.hpp"

#include "infra/detail/infra_strings_internals.hpp"

#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>


html::elements::html_option_element::html_option_element()
{
    INIT_PIMPL(html_option_element);
    ACCESS_PIMPL(html_option_element);

    d->insertion_steps =
            [d]
            {
        decltype(auto) parent = d->parent_node.get();
        return_if (decltype(auto) cast_parent = dom_cast<html_select_element*>(parent))
            detail::selectedness_settings_algorithm(cast_parent);

        decltype(auto) cast_parent = dom_cast<html_opt_group_element*>(d->parent_node.get());
        decltype(auto) cast_grandparent = dom_cast<html_select_element*>(parent->d_func()->parent_node.get());
        return_if (cast_parent && cast_grandparent)
            detail::selectedness_settings_algorithm(cast_grandparent);
            };

    d->remove_steps =
            [d](dom::nodes::node* old_parent)
            {
        decltype(auto) parent = d->parent_node.get();
        return_if (decltype(auto) cast_parent = dom_cast<html_select_element*>(parent))
            detail::selectedness_settings_algorithm(cast_parent);

        decltype(auto) cast_parent = dom_cast<html_opt_group_element*>(d->parent_node.get());
        decltype(auto) cast_grandparent = dom_cast<html_select_element*>(parent->d_func()->parent_node.get());
        return_if (cast_parent && cast_grandparent)
            detail::selectedness_settings_algorithm(cast_grandparent);
            };
}


auto html::elements::html_option_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_option_element);
        return d->disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_option_element);
    decltype(auto) parent = d->parent_node.get();
    return_if (decltype(auto) cast_parent = dom_cast<html_select_element*>(parent))
        cast_parent->d_func()->form_owner.get();

    decltype(auto) cast_parent = dom_cast<html_opt_group_element*>(d->parent_node.get());
    decltype(auto) cast_grandparent = dom_cast<html_select_element*>(parent->d_func()->parent_node.get());
    return_if (cast_parent && cast_grandparent)
        cast_grandparent->d_func()->form_owner.get();
}


auto html::elements::html_option_element::get_label() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_option_element);
        return !d->label.empty() ? d->label : d->text();
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::get_default_selected() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_option_element);
        return d->selected;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::get_selected() const -> ext::boolean
{
    ACCESS_PIMPL(const html_option_element);
    return d->selectedness;
}


auto html::elements::html_option_element::get_value() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_option_element);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::get_text() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_option_element);
        return infra::detail::strip_and_collapse_ascii_whitespace(d->child_nodes
                | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
                | ranges::views::cast_all_to<dom::nodes::text*>()
                | ranges::views::transform([](dom::nodes::text* text) {return text->d_func()->data;})
                | ranges::to<ext::string>);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_option_element);
        return d->disabled = new_disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::set_label(ext::string new_label) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_option_element);
        return d->label = std::move(new_label);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::set_default_selected(ext::boolean new_default_selected) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_option_element);
        return d->selected = new_default_selected;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::set_selected(ext::boolean new_selected) -> ext::boolean
{
    ACCESS_PIMPL(html_option_element);
    d->selectedness = d->dirtiness ? d->selectedness : ext::boolean::TRUE_();
}


auto html::elements::html_option_element::set_value(ext::string new_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_option_element);
        return d->value = new_value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_option_element::set_text(ext::string new_text) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        dom::detail::string_replace_all(std::move(new_text), this);
        // TODO : return (return from above detail method maybe?)
    CE_REACTIONS_METHOD_EXE
}
