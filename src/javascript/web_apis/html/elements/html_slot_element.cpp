#include "html_slot_element.hpp"
#include "html_slot_element_private.hpp"



#include "dom/detail/shadow_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/mixins/slottable.hpp"
#include "dom/mixins/slottable_private.hpp"




html::elements::html_slot_element::html_slot_element()
{
    INIT_PIMPL(html_slot_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_slot_element::assigned_nodes(
        detail::assigned_node_options_t&& options)
        const -> ranges::any_helpful_view<dom::nodes::node*>
{
    ACCESS_PIMPL(const html_slot_element);
    return options[u"flatten"].to<ext::boolean>()
            ? d->assigned_nodes | ranges::views::underlying
            : dom::detail::find_flattened_slottables(this);
}


auto html::elements::html_slot_element::assigned_elements(
        detail::assigned_node_options_t&& options)
        const -> ranges::any_helpful_view<dom::nodes::element*>
{
    ACCESS_PIMPL(const html_slot_element);
    return assigned_nodes(std::move(options))
            | ranges::views::cast<dom::nodes::element*>;
}


auto html::elements::html_slot_element::assign(
        ext::type_is<dom::mixins::slottable*> auto* ...nodes)
        -> void
{
    ACCESS_PIMPL(html_slot_element);
    d->manually_assigned_nodes
            | ranges::views::for_each([](dom::mixins::slottable* slottable) {slottable->d_func()->manual_slot_assignment.reset();});

    auto nodes_set = ext::initializer_list<dom::mixins::slottable*>{nodes...};

    for (decltype(auto) node: nodes_set)
    {
        if (decltype(auto) slot = node->d_func()->manual_slot_assignment)
            slot->d_func()->manual_slot_assignment |= ranges::actions::remove(node);
        node->d_func()->manual_slot_assignment = this;
    }

    d->manually_assigned_nodes = nodes_set;
    dom::detail::assign_slottables_for_tree(dom::detail::root(this));
}