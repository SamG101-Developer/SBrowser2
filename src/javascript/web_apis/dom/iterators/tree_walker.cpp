#include "tree_walker.hpp"

#include "abstract_iterator.hpp"
#include "ext/functional.hpp"

#include "dom/detail/tree_internals.hpp"
#include "dom/detail/traversal_internals.hpp"
#include "dom/iterators/node_filter.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"
#include "dom/other/dom_implementation.hpp"

#include <range/v3/view/cache1.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take_while.hpp>


dom::node_iterators::tree_walker::tree_walker()
        : current_node{nullptr}
{}


auto dom::node_iterators::tree_walker::parent_node()
        -> nodes::node*
{
    decltype(auto) current_node_ancestors = detail::ancestors(d_ptr->current);
    decltype(auto) filtered_ancestors = current_node_ancestors
            | ranges::views::filter(BIND_BACK(detail::filter, this))
            | ranges::views::take_while(BIND_BACK(std::not_equal_to{}, abstract_iterator::d_ptr->root));

    return *filtered_ancestors.begin();
}


auto dom::node_iterators::tree_walker::first_child()
        -> nodes::node*
{
    using detail::traversal_child_t;
    decltype(auto) first_child_node = detail::traverse_children(this, traversal_child_t::FIRST_CHILD);
    return first_child_node;
}


auto dom::node_iterators::tree_walker::last_child()
        -> nodes::node*
{
    using detail::traversal_child_t;
    decltype(auto) last_child_node = detail::traverse_children(this, traversal_child_t::LAST_CHILD);
    return last_child_node;
}


auto dom::node_iterators::tree_walker::prev_sibling()
        -> nodes::node*
{
    using detail::traversal_sibling_t;
    decltype(auto) prev_sibling_node = detail::traverse_siblings(this, traversal_sibling_t::PREVIOUS_SIBLING);
    return prev_sibling_node;
}


auto dom::node_iterators::tree_walker::next_sibling()
        -> nodes::node*
{
    using detail::traversal_sibling_t;
    decltype(auto) next_sibling_node = detail::traverse_siblings(this, traversal_sibling_t::NEXT_SIBLING);
    return next_sibling_node;
}


auto dom::node_iterators::tree_walker::prev_node()
        -> nodes::node*
{
    decltype(auto) node = d_ptr->current;
    while (node != abstract_iterator::d_ptr->root)
    {
        decltype(auto) sibling = node->previous_sibling();
        while (sibling)
        {
            node = sibling;
            auto result = detail::filter(node, this);

            // while the filter 'result' is FILTER_ACCEPT / FILTER_SKIP, and 'node' has child nodes, set 'node' to its
            // last child; 'node' will end up as either a rejected node, or the right-most n-level child of the original
            // 'sibling'
            while (result != node_filter::FILTER_REJECT && node->has_child_nodes())
                result = detail::filter(node = node->last_child(), this);

            // if the final node child that wasn't rejected and doesn't have any child nodes was accepted (not skipped),
            // then set it to the current node and return it - the previous node is the first accepted n-level last
            // child of the previous sibling (so going forward from this node would traverse up the tree and forward to
            // 'sibling'
            if (result == node_filter::FILTER_ACCEPT)
                return d_ptr->current = node;

            // move the sibling back to the previous sibling, as no nodes have been accepted yet (only rejected and
            // skipped), and the previous node has to be a n-level last child of a previous sibling
            sibling = sibling->previous_sibling();
        }

        // the sibling is nullptr, ie there are no more previous siblings under the current parent, so set the node to
        // its parent, and begin checking nodes again (as long as the parent exists and the node isn't 'root', as the
        // parent would be outside the subtree rooted at 'root'); also check the parent first before its siblings
        return_if (!node->parent_node() || node == abstract_iterator::d_ptr->root) nullptr;
        return_if (detail::filter(node = node->parent_node(), this) == node_filter::FILTER_ACCEPT) d_ptr->current = node;
    }
}


auto dom::node_iterators::tree_walker::next_node()
        -> nodes::node*
{
    decltype(auto) node = d_ptr->current;
    decltype(auto) result = node_filter::FILTER_ACCEPT;

    while (true)
    {
        // while the filter 'result' is FILTER_ACCEPT / FILTER_SKIP, and 'node' has child nodes, set 'node' to its
        // first child; 'node' will end up as either a rejected node, or the left-most n-level child of 'node'
        while (result != node_filter::FILTER_REJECT && node->has_child_nodes())
            result = detail::filter(node = node->first_child(), this);

        // if the final node child that wasn't rejected and doesn't have any child nodes was accepted (not skipped),
        // then set it to the current node and return it - the next node is the first accepted n-level first child
        // of the next sibling (so going backwards from this node would traverse down the tree and backwards to
        // 'sibling'
        if (result == node_filter::FILTER_ACCEPT)
            return d_ptr->current = node;

        decltype(auto) temporary = node;
        // next sibling, otherwise parent node to move up tree
        while (temporary)
        {
            return_if(temporary == abstract_iterator::d_ptr->root) nullptr;
            if (decltype(auto) sibling = temporary->next_sibling())
            {
                node = sibling;
                break;
            }
            temporary = temporary->parent_node();
        }

        result = detail::filter(node, this);
        if (result == node_filter::FILTER_ACCEPT)
            return d_ptr->current = node;
    }
}


auto dom::node_iterators::tree_walker::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
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
