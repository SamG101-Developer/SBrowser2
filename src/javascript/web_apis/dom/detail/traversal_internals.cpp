#include "traversal_internals.hpp"
#include "ext/keywords.hpp"

#include "dom/nodes/node.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/iterators/node_iterator.hpp"
#include "dom/iterators/node_filter.hpp"
#include "dom/iterators/tree_walker.hpp"


auto dom::detail::traversal_internals::filter(
        const nodes::node* const node,
        node_iterators::abstract_iterator* const iterator)
        -> ext::number<ushort>
{
    exception_internals::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [iterator] {return iterator->m_active_flag;},
            "NodeIterator/TreeWalker must be inactive to start filtering");

    // get the 'node_type' of the 'node', and if the 'what_to_shot' doesn't have this bit set, then return FILTER_SKIP;
    // if there is no filter, then return FILTER_ACCEPT as everything is automatically accepted. for example, if the
    // 'what_to_show' is '000000000010', only Element nodes ('node_type' == 1) would be accepted
    const auto n = node->node_type() - 1;
    return_if(~(iterator->what_to_show() & (2 << n))) node_iterators::node_filter::FILTER_SKIP;
    return_if(!iterator->filter()) node_iterators::node_filter::FILTER_ACCEPT;

    // begin the filtering with the use function set in the NodeIterator/TreeWalker's filter's 'accept_node' attribute,
    // so set the active flag to true, so that multiple filtering calls don't happen (exception guard at top of method
    // checks this)
    iterator->m_active_flag = true;

    // begin JavaScript error handling in-case the 'accept_node' method throws an error; call the 'accept_node' method
    // with the 'node' as the parameter, and save the result; the result is whether to FILTER_SKIP / FILTER_REJECT /
    // FILTER_ACCEPT the node
    JS_EXCEPTION_HANDLER;
    auto result = iterator->filter()->accept_node()(node);

    // if the method threw an exception, then set the active flag to false (processing has finished), and then rethrow
    // the error; this means that the state of the NodeIterator/TreeWalker has been adjusted for post-filtering, and the
    // error can be managed correctly
    iterator->m_active_flag = false;
    if (JS_EXCEPTION_HAS_THROWN)
        JS_EXCEPTION_RETHROW

    // otherwise, return the result of the filtering process (FILTER_SKIP / FILTER_REJECT / FILTER_ACCEPT
    return result;
}


auto dom::detail::traversal_internals::traverse_children(
        node_iterators::tree_walker* const iterator,
        const traversal_child type)
        -> nodes::node*
{
    using enum traversal_child;

    // set the 'node' to the 'iterator.current_node's first child if the type of iteration is FIRST_CHILD, otherwise the
    // last child (this is just where the iteration will begin from) - this allows for the 'node.child_nodes' to be
    // filtered as before the rest of the tree (which is only for when the child_nodes are all rejected)
    auto* node = type == FIRST_CHILD ? iterator->current_node()->first_child() : iterator->current_node()->last_child();

    // iterate until the node becomes nullptr (or a return statement is called from within the loop, for example when a
    // 'filter(...)' method call returns true
    while (node)
    {

        // filter the 'node' with the 'iterator;, and switch on the result, to decide how to continue, ie is the 'node'
        // accepted, skipped, rejected etc. if the 'node' is accepted, set 'iterator.current_node' to the 'node' and
        // return it. if the 'node' is skipped, set the node to the first / last child and continue filtering
        number_switch(filter(node, iterator))
        {
            number_case(node_iterators::node_filter::FILTER_ACCEPT):
                return iterator->current_node = node;

            number_case(node_iterators::node_filter::FILTER_SKIP):
            {
                auto* const child = type == FIRST_CHILD ? node->first_child() : node->last_child();
                node = child ? child : node;
                continue_if (node == child);
                [[fallthrough]];
            }

            number_case(node_iterators::node_filter::FILTER_REJECT):
                // how to iterate to the next node if 'node' was rejected: if the node as the first child, then set it to its
                // next sibling (if it exists), and if the node was the last child, set it to its previous sibling, if it
                // exists; if not, then set it to its parent (move up the tree), given that is parent isn't the iterators 'root'
                // or 'current_node'
                while (node)
                {
                    // move to next / previous child if it's available
                    if (auto* const sibling = type == FIRST_CHILD ? node->next_sibling() : node->previous_sibling()) {node = sibling; break;}

                    // move to the parent if it's available
                    auto* const parent = node->parent_node();
                    if (!parent || parent == iterator->root() || parent == iterator->current_node()) return nullptr;
                    node = parent;
                }
        }
    }

    // if all the nodes in the tree have been checked, then return a nullptr node
    return nullptr;
}


auto dom::detail::traversal_internals::traverse_siblings(
        node_iterators::tree_walker* const iterator,
        const traversal_sibling type)
        -> nodes::node*
{
    using enum traversal_sibling;

    // set the 'node' to the 'iterator.current_node', and not it's next/previous sibling, because they are in the same
    // hierarchical level as 'node', and so will be automatically iterated to in the method; this is hwy the 'node'
    // cannot be 'iterator.root'; it doesn't have any siblings that are in the descendants of 'iterator.root'
    auto* node = iterator->current_node();
    return_if(node == iterator->root()) nullptr;

    // iterate until a return statement from within the while loop is called (either from an accepted node, or nullptr
    // when the root of the tree reached
    while (node)
    {
        // set the sibling to the next / previous sibling depending on the type,
        auto* sibling = type == NEXT_SIBLING ? node->next_sibling () : node->previous_sibling();

        while (sibling)
        {
            node = sibling;
            number_switch(filter(node, iterator))
            {
                number_case(node_iterators::node_filter::FILTER_ACCEPT):
                    return iterator->current_node = node;

                number_case(node_iterators::node_filter::FILTER_SKIP):
                    sibling = type == NEXT_SIBLING ? node->first_child() : node->last_child();
                    continue_if (sibling);
                    else [[fallthrough]];

                number_case(node_iterators::node_filter::FILTER_REJECT):
                    sibling = type == NEXT_SIBLING ? node->next_sibling() : node->previous_sibling();
            }
        }

        // move to the parent if it's available
        node = node->parent_node();

        return_if (!node || node == iterator->current_node()) nullptr;
        return_if (filter(node, iterator) == node_iterators::node_filter::FILTER_ACCEPT) nullptr;
    }
}
