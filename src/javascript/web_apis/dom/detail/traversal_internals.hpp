#pragma once
#ifndef SBROWSER2_TRAVERSAL_INTERNALS_HPP
#define SBROWSER2_TRAVERSAL_INTERNALS_HPP


#include "ext/type_traits.ixx"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class node;}
namespace dom::node_iterators {class abstract_iterator;}
namespace dom::node_iterators {class node_iterator;}
namespace dom::node_iterators {class tree_walker;}


namespace dom::detail
{
    // filtering
    auto filter(
            const nodes::node* node,
            node_iterators::abstract_iterator* iterator)
            -> ext::number<ushort>;

    // traversal
    auto traverse(
            node_iterators::node_iterator* iterator,
            traversal_direction_t direction)
            -> nodes::node*;

    auto traverse_children(
            node_iterators::tree_walker* iterator,
            traversal_child_t type)
            -> nodes::node*;

    auto traverse_siblings(
            node_iterators::tree_walker* iterator,
            traversal_sibling_t type)
            -> nodes::node*;
}


#endif //SBROWSER2_TRAVERSAL_INTERNALS_HPP
