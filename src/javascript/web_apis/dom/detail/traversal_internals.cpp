

auto dom::detail::traverse_children(
        node_iterators::tree_walker* const iterator,
        const traversal_child_t type)
        -> nodes::node*
{
    using enum traversal_child_t;

    // set the 'node' to the 'iterator.current_node's first child if the type of iteration is FIRST_CHILD, otherwise the
    // last child (this is just where the iteration will begin from) - this allows for the 'node.child_nodes' to be
    // filtered as before the rest of the tree (which is only for when the child_nodes are all rejected)
    decltype(auto) node = type == FIRST_CHILD
            ? detail::first_child(iterator->d_func()->current)
            : detail::last_child(iterator->d_func()->current);

    // iterate until the node becomes nullptr (or a return statement is called from within the loop, for example when a
    // 'filter(...)' method call returns true
    while (node)
    {

        // filter the 'node' with the 'iterator;, and switch on the result, to decide how to continue, ie is the 'node'
        // accepted, skipped, rejected etc. if the 'node' is accepted, set 'iterator.current_node' to the 'node' and
        // return it. if the 'node' is skipped, set the node to the first / last child and continue filtering
        switch(*filter(node, iterator))
        {
            case *node_iterators::node_filter::FILTER_ACCEPT:
                return iterator->d_func()->current = node;

            case *node_iterators::node_filter::FILTER_SKIP:
            {
                decltype(auto) child = type == FIRST_CHILD ? detail::first_child(node) : detail::last_child(node);

                node = child ?: node;
                continue_if (node == child);
            }

            case *node_iterators::node_filter::FILTER_REJECT:
                // how to iterate to the next node if 'node' was rejected: if the node as the first child, then set it
                // to its next sibling (if it exists), and if the node was the last child, set it to its previous
                // sibling, if it exists; if not, then set it to its parent (move up the tree), given that is parent
                // isn't the iterators 'root' or 'current_node'
                while (node)
                {
                    // move to next / previous child if it's available
                    if (decltype(auto) sibling = type == FIRST_CHILD ? next_sibling(node) : previous_sibling(node))
                    {
                        node = sibling;
                        break;
                    }

                    // move to the parent if it's available
                    decltype(auto) parent = node->d_func()->parent_node;
                    return_if (!parent || parent == iterator->d_func()->root || parent == iterator->d_func()->current) nullptr;
                    node = parent;
                }
        }
    }

    // if all the nodes in the tree have been checked, then return a nullptr node
    return nullptr;
}


auto dom::detail::traverse_siblings(
        node_iterators::tree_walker* const iterator,
        const traversal_sibling_t type)
        -> nodes::node*
{
    using enum traversal_sibling_t;

    // set the 'node' to the 'iterator.current_node', and not it's next/previous sibling, because they are in the same
    // hierarchical level as 'node', and so will be automatically iterated to in the method; this is hwy the 'node'
    // cannot be 'iterator.root'; it doesn't have any siblings that are in the descendants of 'iterator.root'
    auto* node = iterator->d_func()->current;
    return_if(node == iterator->d_func()->root) nullptr;

    // iterate until a return statement from within the while loop is called (either from an accepted node, or nullptr
    // when the root of the tree reached
    while (node)
    {
        // set the sibling to the next / previous sibling depending on the type,
        auto* sibling = type == NEXT_SIBLING
                ? detail::next_sibling(node)
                : detail::previous_sibling(node);

        while (sibling)
        {
            node = sibling;
            switch(*filter(node, iterator))
            {
                case(*node_iterators::node_filter::FILTER_ACCEPT):
                    return iterator->d_func()->current = node;

                case(*node_iterators::node_filter::FILTER_SKIP):
                    sibling = type == NEXT_SIBLING ? first_child(node) : last_child(node);
                    continue_if (sibling);
                    else [[fallthrough]];

                case(*node_iterators::node_filter::FILTER_REJECT):
                    sibling = type == NEXT_SIBLING ? next_sibling(node) : previous_sibling(node);
            }
        }

        // move to the parent if it's available
        node = node->d_func()->parent_node;

        return_if (!node || node == iterator->d_func()->current) nullptr;
        return_if (filter(node, iterator) == node_iterators::node_filter::FILTER_ACCEPT) nullptr;
    }
}
