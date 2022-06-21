#ifndef SBROWSER2_SHADOW_INTERNALS_HPP
#define SBROWSER2_SHADOW_INTERNALS_HPP

#include <ext/vector.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/shadow_root.hpp>
#include <web_apis/dom/mixins/slottable.hpp>
#include <range/v3/algorithm/contains.hpp>
namespace html::elements {class html_slot_element;}


namespace dom::detail::shadow_internals
{
    // shadow checks
    static auto is_connected(
            nodes::node* node_a)
            -> bool;

    static auto is_slot(
            nodes::node* node_a)
            -> bool;

    static auto is_slottable(
            nodes::node* node_a)
            -> bool;

    static auto is_assigned(
            nodes::node* node_a)
            -> bool;

    // tree based shadow checks
    static auto is_root_shadow_root(
            nodes::node* node_a)
            -> nodes::shadow_root*;

    static auto is_shadow_root(
            nodes::node* node_a)
            -> bool;

    static auto is_shadow_host(
            nodes::node* node_a)
            -> bool;

    static auto shadow_including_descendants(
            nodes::node* node_a)
            -> range_v3_view auto;

    static auto is_shadow_including_descendant(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    static auto is_shadow_including_ancestor(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    static auto is_host_including_ancestor(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    static auto is_closed_shadow_hidden(
            nodes::node* node_a,
            nodes::node* node_b)
            -> bool;

    // find slots and slottables
    static auto find_slot(
            nodes::node* slottable,
            bool open_flag = false)
            -> html::elements::html_slot_element*;

    static auto find_slottables(
            html::elements::html_slot_element* slot)
            -> range_v3_view auto;

    static auto find_flattened_slottables(
            html::elements::html_slot_element* slot)
            -> range_v3_view auto;

    // assign slots and slottables
    static auto assign_slot(
            nodes::node* slottable)
            -> void;

    static auto assign_slottables(
            html::elements::html_slot_element* slot)
            -> void;

    static auto assign_slottables_for_tree(
            nodes::node* descendant)
            -> void;

    // other general helper methods for shadows
    static auto signal_slot_change(
            nodes::node* slot)
            -> void;

    static auto shadow_including_root(
            nodes::node* node_a)
            -> nodes::node*;

    static auto retarget(
            nodes::event_target* event_target_a,
            nodes::event_target* event_target_b)
            -> nodes::event_target*;

    static auto shadow_root(
            nodes::node* node_a)
            -> nodes::shadow_root*;
}


auto dom::detail::shadow_internals::is_connected(nodes::node* node_a) -> bool
{
    // 'node_a' is connected if the shadow-including-root is document node (in other words, the node isn't in a shadow
    // tree (root is a shadow root), but is in a normal tree (root is a document node)
    return dynamic_cast<nodes::document*>(shadow_including_root(node_a));
}


auto dom::detail::shadow_internals::is_slot(nodes::node* node_a) -> bool
{
    // 'node_a' is a slot if the shadow-including-root is a shadow root (in other wised, the node is in a shadow tree
    // (root is a shadow root)
    return is_root_shadow_root(node_a);
}


auto dom::detail::shadow_internals::is_slottable(nodes::node* node_a) -> bool
{
    // 'node_a' is slottable if it has inherited the slottable<T> mixin (element node or text node at present, but could
    // change, so check for the mixin as a base class)
    return dynamic_cast<mixins::slottable*>(node_a) != nullptr;
}


auto dom::detail::shadow_internals::is_assigned(nodes::node* node_a) -> bool
{
    // 'node_a' is assigned if it is a slottable whose assigned slot is not nullptr
    return is_slottable(node_a) && dynamic_cast<mixins::slottable*>(node_a)->assigned_slot();
}


auto dom::detail::shadow_internals::is_root_shadow_root(nodes::node* node_a) -> nodes::shadow_root*
{
    // 'node_a''s root is a shadow root if it can be cast to the dom::nodes::shadow_root class
    return dynamic_cast<nodes::shadow_root*>(tree_internals::root(node_a));
}


auto dom::detail::shadow_internals::is_shadow_root(nodes::node* node_a) -> bool
{
    // 'node_a' is a shadow root if it can be cast to the dom::nodes::shadow_root class
    return dynamic_cast<nodes::shadow_root*>(node_a) != nullptr;
}


auto dom::detail::shadow_internals::is_shadow_host(nodes::node* node_a) -> bool
{
    // 'node_a' is a shadow host if it has the 'shadow_root_node' attribute set
    auto* element = dynamic_cast<nodes::element*>(node_a);
    return element && element->shadow_root_node();
}


auto dom::detail::shadow_internals::shadow_including_descendants(nodes::node* node_a) -> range_v3_view auto
{
    // 'node_a''s shadow including descendants are the TODO
    auto descendants = tree_internals::descendants(node_a);
    return descendants;
}


auto dom::detail::shadow_internals::is_shadow_including_descendant(nodes::node* node_a, nodes::node* node_b) -> bool
{
    // 'node_a' is a shadow including descendant of 'node_b' if 'node_a' is a normal descendant of 'node_b', or if
    // 'node_a''s shadow root's host is a shadow including descendant of the 'node_b' (ie bridge up from the shadow tree
    // into the next tree)
    if (!node_a || !node_b) return false;
    return ranges::contains(shadow_including_descendants(node_b), node_a)
            || is_shadow_including_descendant(is_root_shadow_root(node_a)->host, node_b);
}


auto dom::detail::shadow_internals::is_shadow_including_ancestor(nodes::node* node_a, nodes::node* node_b) -> bool
{
    // 'node_a' is a shadow including ancestor of 'node_b', if the 'node_b' is a shadow including descendant of 'node_a'
    if (!node_a || !node_b) return false;
    return is_shadow_including_descendant(node_b, node_a);
}


auto dom::detail::shadow_internals::is_host_including_ancestor(nodes::node* node_a, nodes::node* node_b) -> bool
{
    return tree_internals::is_descendant(node_a, node_b) || is_shadow_including_ancestor(node_a, is_root_shadow_root(node_b)->host);
}


#endif //SBROWSER2_SHADOW_INTERNALS_HPP
