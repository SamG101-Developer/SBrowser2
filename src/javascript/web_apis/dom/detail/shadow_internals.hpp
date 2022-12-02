#ifndef SBROWSER2_SHADOW_INTERNALS_HPP
#define SBROWSER2_SHADOW_INTERNALS_HPP

#include "ext/boolean.ixx"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::mixins {class slottable;}
namespace dom::nodes {class event_target;}
namespace dom::nodes {class node;}
namespace dom::nodes {class shadow_root;}
namespace html::elements {class html_slot_element;}


namespace dom::detail
{
    // shadow checks
    auto is_connected(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_slot(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_slottable(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_assigned(
            const nodes::node* node_a)
            -> ext::boolean;

    // tree based shadow checks
    auto is_root_shadow_root(
            const nodes::node* node_a)
            -> nodes::shadow_root*;

    auto is_shadow_root(
            const nodes::node* node_a)
            -> ext::boolean;

    auto is_shadow_host(
            const nodes::node* node_a)
            -> ext::boolean;

    auto shadow_including_descendants(
            const nodes::node* node_a)
            -> ranges::any_view<nodes::node*>;

    auto is_shadow_including_descendant(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_shadow_including_ancestor(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_host_including_ancestor(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    auto is_closed_shadow_hidden(
            const nodes::node* node_a,
            const nodes::node* node_b)
            -> ext::boolean;

    // find slots and slottables
    auto find_slot(
            const nodes::node* slottable,
            ext::boolean open_flag = false)
            -> html::elements::html_slot_element*;

    auto find_slottables(
            const html::elements::html_slot_element* slot)
            -> ranges::any_view<dom::mixins::slottable*>; // TODO <- correct template type?

    auto find_flattened_slottables(
            const html::elements::html_slot_element* slot)
            -> ranges::any_view<dom::mixins::slottable*>; // TODO <- correct template type?

    // assign slots and slottables
    auto assign_slot(
            const nodes::node* slottable)
            -> void;

    auto assign_slottables(
            const html::elements::html_slot_element* slot)
            -> void;

    auto assign_slottables_for_tree(
            const nodes::node* descendant)
            -> void;

    // other general helper methods for shadows
    auto signal_slot_change(
            const nodes::node* slot)
            -> void;

    auto shadow_including_root(
            const nodes::node* node_a)
            -> nodes::node*;

    auto retarget(
            const nodes::event_target* event_target_a,
            const nodes::event_target* event_target_b)
            -> nodes::event_target*;

    auto shadow_root(
            const nodes::node* node_a)
            -> nodes::shadow_root*;
}


#endif //SBROWSER2_SHADOW_INTERNALS_HPP
