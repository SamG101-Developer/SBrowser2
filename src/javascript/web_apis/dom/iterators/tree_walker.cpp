#include "tree_walker.hpp"
#include "tree_walker_private.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/detail/tree_internals.hpp"
#include "dom/detail/traversal_internals.hpp"
#include "dom/iterators/node_filter.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/other/dom_implementation.hpp"

#include <range/v3/view/cache1.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take_while.hpp>


dom::node_iterators::tree_walker::tree_walker()
{
    INIT_PIMPL(tree_walker);

    ACCESS_PIMPL(tree_walker);
    d->current = nullptr;
}


auto dom::node_iterators::tree_walker::parent_node() -> nodes::node*
{
    ACCESS_PIMPL(tree_walker);

    // The parent node of a TreeWalker is the furthest away ancestor (highest in the tree), that passes the 'filter',
    // and isn't equal to
    decltype(auto) current_node_ancestors = detail::ancestors(d->current.get());
    decltype(auto) filtered_ancestors = current_node_ancestors
            | ranges::views::filter_fn_eq(BIND_BACK(detail::filter, this), node_filter::FILTER_ACCEPT)
            | ranges::views::take_while(BIND_BACK(ext::cmp::eq, d->root.get()));

    return filtered_ancestors.front();
}


auto dom::node_iterators::tree_walker::first_child() -> nodes::node*
{
    // The first child of a TreeWalker is obtained by the traversing children detail method, with the FIRST_CHILD
    // configuration.
    using detail::traversal_child_t;
    decltype(auto) first_child_node = detail::traverse_children(this, traversal_child_t::FIRST_CHILD);
    return first_child_node;
}


auto dom::node_iterators::tree_walker::last_child() -> nodes::node*
{
    // The last child of a TreeWalker is obtained by the traversing children detail method, with the LAST_CHILD
    // configuration.
    using detail::traversal_child_t;
    decltype(auto) last_child_node = detail::traverse_children(this, traversal_child_t::LAST_CHILD);
    return last_child_node;
}


auto dom::node_iterators::tree_walker::prev_sibling() -> nodes::node*
{
    // The prev sibling of a TreeWalker is obtained by the traversing children detail method, with the PREVIOUS_SIBLING
    // configuration.
    using detail::traversal_sibling_t;
    decltype(auto) prev_sibling_node = detail::traverse_siblings(this, traversal_sibling_t::PREVIOUS_SIBLING);
    return prev_sibling_node;
}


auto dom::node_iterators::tree_walker::next_sibling() -> nodes::node*
{
    // The next sibling of a TreeWalker is obtained by the traversing children detail method, with the NEXT_SIBLING
    // configuration.
    using detail::traversal_sibling_t;
    decltype(auto) next_sibling_node = detail::traverse_siblings(this, traversal_sibling_t::NEXT_SIBLING);
    return next_sibling_node;
}


auto dom::node_iterators::tree_walker::prev_node() -> nodes::node*
{
    ACCESS_PIMPL(tree_walker);

    decltype(auto) node = d->current.get();
    while (node != d->root.get())
    {
        decltype(auto) sibling = detail::previous_sibling(node);
        while (sibling)
        {
            node = sibling;
            auto result = detail::filter(node, this);

            // While the filter 'result' is FILTER_ACCEPT / FILTER_SKIP, and 'node' has child nodes, set 'node' to its
            // last child; 'node' will end up as either a rejected node, or the right-most n-level child of the original
            // 'sibling'.
            while (result != node_filter::FILTER_REJECT && node->has_child_nodes())
                result = detail::filter(node = detail::last_child(node), this);

            // If the final node child that wasn't rejected and doesn't have any child nodes was accepted (not skipped),
            // then set it to the current node and return it - the previous node is the first accepted n-level last
            // child of the previous sibling (so going forward from this node would traverse up the tree and forward to
            // 'sibling'.
            if (result == node_filter::FILTER_ACCEPT)
                return (d->current = node).get();

            // Move the sibling back to the previous sibling, as no nodes have been accepted yet (only rejected and
            // skipped), and the previous node has to be a n-level last child of a previous sibling
            sibling = detail::previous_sibling(sibling);
        }

        // The sibling is nullptr, ie there are no more previous siblings under the current parent, so set the node to
        // its parent, and begin checking nodes again (as long as the parent exists and the node isn't 'root', as the
        // parent would be outside the subtree rooted at 'root'); also check the parent first before its siblings
        return_if (!node->d_func()->parent_node || node == d_func()->root) nullptr;
        return_if (detail::filter(node = node->d_func()->parent_node, this) == node_filter::FILTER_ACCEPT) (d->current = node).get();
    }
}


auto dom::node_iterators::tree_walker::next_node() -> nodes::node*
{
    ACCESS_PIMPL(tree_walker);

    decltype(auto) node = d->current;
    decltype(auto) result = node_filter::FILTER_ACCEPT;

    while (true)
    {
        // While the filter 'result' is FILTER_ACCEPT / FILTER_SKIP, and 'node' has child nodes, set 'node' to its
        // first child; 'node' will end up as either a rejected node, or the left-most n-level child of 'node'
        while (result != node_filter::FILTER_REJECT && node->has_child_nodes())
            result = detail::filter(node = detail::first_child(node), this);

        // If the final node child that wasn't rejected and doesn't have any child nodes was accepted (not skipped),
        // then set it to the current node and return it - the next node is the first accepted n-level first child
        // of the next sibling (so going backwards from this node would traverse down the tree and backwards to
        // 'sibling'
        if (result == node_filter::FILTER_ACCEPT)
            return d->current = node;

        decltype(auto) temporary = node;
        // next sibling, otherwise parent node to move up tree
        while (temporary)
        {
            return_if(temporary == d->root) nullptr;
            if (decltype(auto) sibling = detail::next_sibling(temporary))
            {
                node = sibling;
                break;
            }
            temporary = temporary->d_func()->parent_node;
        }

        result = detail::filter(node, this);
        if (result == node_filter::FILTER_ACCEPT)
            return d->current = node;
    }
}


auto dom::node_iterators::tree_walker::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<tree_walker>{isolate}
        .inherit<abstract_iterator>()
        .function("parentNode", &tree_walker::parent_node)
        .function("firstChild", &tree_walker::first_child)
        .function("lastChild", &tree_walker::last_child)
        .function("nextSibling", &tree_walker::next_sibling)
        .function("previousSibling", &tree_walker::prev_sibling)
        .function("nextNode", &tree_walker::next_node)
        .function("previousNode", &tree_walker::prev_node)
        .property("currentNode", &tree_walker::get_current_node, &tree_walker::set_current_node)
        .auto_wrap_objects();

    return std::move(conversion);
}
