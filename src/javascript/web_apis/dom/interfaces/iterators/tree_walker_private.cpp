module;
#include "ext/macros.hpp"


module apis.dom.tree_walker:p;
import apis.dom.node;
import apis.dom.node_filter;

import ext.core;


auto dom::tree_walker_private::traverse_children(traversal_child_t type) -> node*
{
    using enum traversal_child_t;

    // set the 'node' to the 'iterator.current_node's first child if the type of iteration is FIRST_CHILD, otherwise the
    // last child (this is just where the iteration will begin from) - this allows for the 'node.child_nodes' to be
    // filtered as before the rest of the tree (which is only for when the child_nodes are all rejected)
    decltype(auto) node = type == FIRST_CHILD
            ? current->d_func()->first_child()
            : current->d_func()->last_child();

    // iterate until the node becomes nullptr (or a return statement is called from within the loop, for example when a
    // 'filter(...)' method call returns true
    while (node)
    {

        // filter the 'node' with the 'iterator;, and switch on the result, to decide how to continue, ie is the 'node'
        // accepted, skipped, rejected etc. if the 'node' is accepted, set 'iterator.current_node' to the 'node' and
        // return it. if the 'node' is skipped, set the node to the first / last child and continue filtering
        switch(*filter(node))
        {
            case *node_filter::FILTER_ACCEPT:
                return current = node;

            case *node_filter::FILTER_SKIP:
            {
                decltype(auto) child = type == FIRST_CHILD ? node->d_func()->first_child() : node->d_func()->last_child();
                node = child ?: node;
                continue_if (node == child);
            }

            case *node_filter::FILTER_REJECT:
                // how to iterate to the next node if 'node' was rejected: if the node as the first child, then set it
                // to its next sibling (if it exists), and if the node was the last child, set it to its previous
                // sibling, if it exists; if not, then set it to its parent (move up the tree), given that is parent
                // isn't the iterators 'root' or 'current_node'
                while (node)
                {
                    // move to next / previous child if it's available
                    if (decltype(auto) sibling = type == FIRST_CHILD ? node->d_func()->next_sibling() : node->d_func()->prev_sibling())
                    {
                        node = sibling;
                        break;
                    }

                    // move to the parent if it's available
                    decltype(auto) parent = node->d_func()->parent_node.get();
                    return_if (!parent || parent == root.get() || parent == current.get()) nullptr;
                    node = parent;
                }
        }
    }

    // if all the nodes in the tree have been checked, then return a nullptr node
    return nullptr;
}


auto dom::tree_walker_private::traverse_siblings(traversal_sibling_t type) -> node*
{
    using enum traversal_sibling_t;

    // set the 'node' to the 'iterator.current_node', and not it's next/previous sibling, because they are in the same
    // hierarchical level as 'node', and so will be automatically iterated to in the method; this is hwy the 'node'
    // cannot be 'iterator.root'; it doesn't have any siblings that are in the descendants of 'iterator.root'
    decltype(auto) node = current.get();
    return_if(node == root.get()) nullptr;

    // iterate until a return statement from within the while loop is called (either from an accepted node, or nullptr
    // when the root of the tree reached
    while (node)
    {
        // set the sibling to the next / previous sibling depending on the type,
        auto* sibling = type == NEXT_SIBLING
                ? node->d_func()->next_sibling()
                : node->d_func()->prev_sibling();

        while (sibling)
        {
            node = sibling;
            switch(*filter(node))
            {
                case(*node_filter::FILTER_ACCEPT):
                    return (current = node).get();

                case(*node_filter::FILTER_SKIP):
                    sibling = type == NEXT_SIBLING ? node->d_func()->first_child() : node->d_func()->last_child();
                    continue_if (sibling);
                    else [[fallthrough]];

                case(*node_filter::FILTER_REJECT):
                    sibling = type == NEXT_SIBLING ? node->d_func()->next_sibling() : node->d_func()->prev_sibling();
            }
        }

        // move to the parent if it's available
        node = node->d_func()->parent_node.get();

        return_if (!node || node == current.get()) nullptr;
        return_if (filter(node) == node_filter::FILTER_ACCEPT) nullptr;
    }

    return nullptr;
}
