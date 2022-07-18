#pragma once
#ifndef SBROWSER2_TRAVERSAL_INTERNALS_HPP
#define SBROWSER2_TRAVERSAL_INTERNALS_HPP

#include "ext/number.hpp"
namespace dom::nodes {class node;}
namespace dom::node_iterators {class abstract_iterator;}
namespace dom::node_iterators {class node_iterator;}
namespace dom::node_iterators {class tree_walker;}


namespace dom::detail::traversal_internals
{
    enum class traversal_direction {NEXT, PREVIOUS};
    enum class traversal_child {FIRST_CHILD, LAST_CHILD};
    enum class traversal_sibling {NEXT_SIBLING, PREVIOUS_SIBLING};

    // filtering
    auto filter(
            const nodes::node* node,
            node_iterators::abstract_iterator* iterator)
            -> ext::number<ushort>;

    // traversal
    auto traverse(
            node_iterators::node_iterator* iterator,
            traversal_direction direction)
            -> nodes::node*;

    auto traverse_children(
            node_iterators::tree_walker* iterator,
            traversal_child type)
            -> nodes::node*;

    auto traverse_siblings(
            node_iterators::tree_walker* iterator,
            traversal_sibling type)
            -> nodes::node*;
}


#endif //SBROWSER2_TRAVERSAL_INTERNALS_HPP
