module;
#include "ext/macros/pimpl.hpp"
#include "ext/macros/language_shorthand.hpp"
#include "javascript/macros/expose.hpp"
#include <range/v3/view/cache1.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take_while.hpp>


module apis.dom.tree_walker;
import apis.dom.tree_walker_private;
import apis.dom.node;
import apis.dom.node_private;
import apis.dom.node_filter;
import apis.dom.node_filter_private;

import ext.core;
import js.env.module_type;


dom::tree_walker::tree_walker()
{
    INIT_PIMPL; ACCESS_PIMPL;
    d->current = nullptr;
}


auto dom::tree_walker::parent_node() -> node*
{
    ACCESS_PIMPL;

    // The parent node of a TreeWalker is the furthest away ancestor (highest in the tree), that passes the 'filter',
    // and isn't equal to
    decltype(auto) current_node_ancestors = d->current->d_func()->ancestors();
    decltype(auto) filtered_ancestors = current_node_ancestors
            | ranges::views::filter(&tree_walker_private::filter, node_filter::FILTER_ACCEPT)
            | ranges::views::take_while(ext::bind_back(ext::cmp::eq, d->root.get()));

    return filtered_ancestors.front();
}


auto dom::tree_walker::first_child() -> node*
{
    // The first child of a TreeWalker is obtained by the traversing children detail method, with the FIRST_CHILD
    // configuration.
    ACCESS_PIMPL;
    using enum tree_walker_private::traversal_child_t;
    decltype(auto) first_child_node = d->traverse_children(FIRST_CHILD);
    return first_child_node;
}


auto dom::tree_walker::last_child() -> node*
{
    // The last child of a TreeWalker is obtained by the traversing children detail method, with the LAST_CHILD
    // configuration.
    ACCESS_PIMPL;
    using enum tree_walker_private::traversal_child_t;
    decltype(auto) last_child_node = d->traverse_children(LAST_CHILD);
    return last_child_node;
}


auto dom::tree_walker::prev_sibling() -> node*
{
    // The prev sibling of a TreeWalker is obtained by the traversing children detail method, with the PREVIOUS_SIBLING
    // configuration.
    ACCESS_PIMPL;
    using enum tree_walker_private::traversal_sibling_t;
    decltype(auto) prev_sibling_node = d->traverse_siblings(PREVIOUS_SIBLING);
    return prev_sibling_node;
}


auto dom::tree_walker::next_sibling() -> node*
{
    // The next sibling of a TreeWalker is obtained by the traversing children detail method, with the NEXT_SIBLING
    // configuration.
    ACCESS_PIMPL;
    using enum tree_walker_private::traversal_sibling_t;
    decltype(auto) next_sibling_node = d->traverse_siblings(NEXT_SIBLING);
    return next_sibling_node;
}


auto dom::tree_walker::prev_node() -> node*
{
    ACCESS_PIMPL;

    decltype(auto) node = d->current.get();
    while (node != d->root.get())
    {
        decltype(auto) sibling = node->d_func()->prev_sibling();
        while (sibling)
        {
            node = sibling;
            auto result = d->filter(node);

            // While the filter 'result' is FILTER_ACCEPT / FILTER_SKIP, and 'node' has child nodes, set 'node' to its
            // last child; 'node' will end up as either a rejected node, or the right-most n-level child of the original
            // 'sibling'.
            while (result != node_filter::FILTER_REJECT && node->has_child_nodes())
                result = d->filter(node = node->d_func()->last_child());

            // If the final node child that wasn't rejected and doesn't have any child nodes was accepted (not skipped),
            // then set it to the current node and return it - the previous node is the first accepted n-level last
            // child of the previous sibling (so going forward from this node would traverse up the tree and forward to
            // 'sibling'.
            if (result == node_filter::FILTER_ACCEPT)
                return (d->current = node).get();

            // Move the sibling back to the previous sibling, as no nodes have been accepted yet (only rejected and
            // skipped), and the previous node has to be a n-level last child of a previous sibling
            sibling = sibling->d_func()->previous_sibling();
        }

        // The sibling is nullptr, ie there are no more previous siblings under the current parent, so set the node to
        // its parent, and begin checking nodes again (as long as the parent exists and the node isn't 'root', as the
        // parent would be outside the subtree rooted at 'root'); also check the parent first before its siblings
        return_if (!node->d_func()->parent_node || node == d_func()->root.get()) nullptr;
        return_if (d->filter(node = node->d_func()->parent_node, this) == node_filter::FILTER_ACCEPT) (d->current = node).get();
    }
}


auto dom::tree_walker::next_node() -> node*
{
    ACCESS_PIMPL;

    decltype(auto) node = d->current.get();
    auto result = node_filter::FILTER_ACCEPT;

    while (true)
    {
        // While the filter 'result' is FILTER_ACCEPT / FILTER_SKIP, and 'node' has child nodes, set 'node' to its
        // first child; 'node' will end up as either a rejected node, or the left-most n-level child of 'node'
        while (result != node_filter::FILTER_REJECT && node->has_child_nodes())
            result = d->filter(node = node->d_func()->first_child());

        // If the final node child that wasn't rejected and doesn't have any child nodes was accepted (not skipped),
        // then set it to the current node and return it - the next node is the first accepted n-level first child
        // of the next sibling (so going backwards from this node would traverse down the tree and backwards to
        // 'sibling'
        if (result == node_filter::FILTER_ACCEPT)
            return (d->current = node).get();

        decltype(auto) temporary = node;
        // next sibling, otherwise parent node to move up tree
        while (temporary)
        {
            return_if(temporary == d->root.get()) nullptr;
            if (decltype(auto) sibling = temporary->d_func()->next_sibling())
            {
                node = sibling;
                break;
            }
            temporary = temporary->d_func()->parent_node.get();
        }

        result = d->filter(node);
        if (result == node_filter::FILTER_ACCEPT)
            return (d->current = node).get();
    }
}


auto dom::tree_walker::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
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

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
