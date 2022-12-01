#include "shadow_internals.hpp"

#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/shadow_root_private.hpp"

#include <range/v3/algorithm/contains.hpp>


auto dom::detail::is_connected(
        const nodes::node* const node_a)
        -> ext::boolean
{
    // 'node_a' is connected if the shadow-including-root is document node (in other words, the node isn't in a shadow
    // tree (root is a shadow root), but is in a normal tree (root is a document node).
    return node_a && dynamic_cast<nodes::document*>(shadow_including_root(node_a));
}


auto dom::detail::is_slot(
        const nodes::node* const node_a)
        -> ext::boolean
{
    // 'node_a' is a slot if the shadow-including-root is a shadow root (in other wised, the node is in a shadow tree
    // (root is a shadow root).
    return node_a && is_root_shadow_root(node_a);
}


auto dom::detail::is_slottable(
        const nodes::node* const node_a)
        -> ext::boolean
{
    // 'node_a' is slottable if it has inherited the slottable<T> mixin (element node or text node at present, but could
    // change, so check for the mixin as a base class).
    return node_a && dynamic_cast<const mixins::slottable*>(node_a);
}


auto dom::detail::is_assigned(
        const nodes::node* const node_a)
        -> ext::boolean
{
    // 'node_a' is assigned if it is a slottable whose assigned slot is not nullptr.
    return node_a && is_slottable(node_a) && dom_cross_cast<const mixins::slottable*>(node_a)->d_func()->assigned_slot;
}


auto dom::detail::is_root_shadow_root(
        const nodes::node* const node_a)
        -> nodes::shadow_root*
{
    // 'node_a''s root is a shadow root if it can be cast to the dom::nodes::shadow_root class.
    return node_a ? dynamic_cast<nodes::shadow_root*>(root(node_a)) : nullptr;
}


auto dom::detail::is_shadow_root(
        const nodes::node* const node_a)
        -> ext::boolean
{
    // 'node_a' is a shadow root if it can be cast to the dom::nodes::shadow_root class.
    return node_a && dynamic_cast<const nodes::shadow_root*>(node_a);
}


auto dom::detail::is_shadow_host(
        const nodes::node* const node_a)
        -> ext::boolean
{
    // 'node_a' is a shadow host if it has the 'shadow_root_node' attribute set.
    const auto* const element = dynamic_cast<const nodes::element*>(node_a);
    return element && element->d_func()->shadow_root;
}


auto dom::detail::shadow_including_descendants(
        const nodes::node* node_a)
        -> ranges::any_view<nodes::node*>
{
    // 'node_a''s shadow including descendants are the TODO
    const auto shadow_including_descendants = descendants(node_a);
    return shadow_including_descendants;
}


auto dom::detail::is_shadow_including_descendant(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' is a shadow including descendant of 'node_b' if 'node_a' is a normal descendant of 'node_b', or if
    // 'node_a''s shadow root's host is a shadow including descendant of the 'node_b' (ie bridge up from the shadow tree
    // into the next tree).
    if (!node_a || !node_b) return false;
    return ranges::contains(shadow_including_descendants(node_b), node_a) || is_shadow_including_descendant(is_root_shadow_root(node_a)->d_func()->host, node_b);
}


auto dom::detail::is_shadow_including_ancestor(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    // 'node_a' is a shadow including ancestor of 'node_b', if the 'node_b' is a shadow including descendant of 'node_a'.
    if (!node_a || !node_b) return false;
    return is_shadow_including_descendant(node_b, node_a);
}


auto dom::detail::is_host_including_ancestor(
        const nodes::node* const node_a,
        const nodes::node* const node_b)
        -> ext::boolean
{
    return is_descendant(node_a, node_b) || is_shadow_including_ancestor(node_a, is_root_shadow_root(node_b)->d_func()->host);
}
