#ifndef SBROWSER2_SHADOW_INTERNALS_HPP
#define SBROWSER2_SHADOW_INTERNALS_HPP

#include <ext/vector.hpp>
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class event_target;}
namespace dom::nodes {class node;}
namespace html::elements {class html_slot_element;}


namespace dom::detail::shadow_internals
{
    // shadow checks
    auto is_connected(
            nodes::node* node_a)
            -> bool;

    auto is_slot(
            nodes::node* node_a)
            -> bool;

    auto is_slottable(
            nodes::node* node_a)
            -> bool;

    auto is_assigned(
            nodes::node* node_a)
            -> bool;

    // tree based shadow checks
    auto is_root_shadow_root(
            nodes::node* node_a)
            -> nodes::shadow_root*;

    auto is_shadow_root(
            nodes::node* node_a)
            -> bool;

    auto is_shadow_host(
            nodes::node* node_a)
            -> bool;

    auto shadow_including_descendants(
            nodes::node* node_a)
            -> range_v3_view auto;

    auto is_shadow_including_descendant(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    auto is_shadow_including_ancestor(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    auto is_host_including_ancestor(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    auto is_closed_shadow_hidden(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    // find slots and slottables
    auto find_slot(
            nodes::node* slottable,
            bool open_flag = false)
            -> html::elements::html_slot_element*;

    auto find_slottables(
            html::elements::html_slot_element* slot)
            -> ranges::any_view<html::elements::html_slot_element*>; // TODO <- correct template type?

    auto find_flattened_slottables(
            html::elements::html_slot_element* slot)
            -> ranges::any_view<html::elements::html_slot_element*>; // TODO <- correct template type?

    // assign slots and slottables
    auto assign_slot(
            nodes::node* slottable)
            -> void;

    auto assign_slottables(
            html::elements::html_slot_element* slot)
            -> void;

    auto assign_slottables_for_tree(
            nodes::node* descendant)
            -> void;

    // other general helper methods for shadows
    auto signal_slot_change(
            nodes::node* slot)
            -> void;

    auto shadow_including_root(
            nodes::node* node_a)
            -> nodes::node*;

    auto retarget(
            nodes::event_target* event_target_a,
            nodes::event_target* event_target_b)
            -> nodes::event_target*;

    auto shadow_root(
            nodes::node* node_a)
            -> nodes::shadow_root*;
}


#endif //SBROWSER2_SHADOW_INTERNALS_HPP
