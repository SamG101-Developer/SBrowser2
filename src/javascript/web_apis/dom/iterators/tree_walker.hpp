#pragma once
#ifndef SBROWSER2_TREE_WALKER_HPP
#define SBROWSER2_TREE_WALKER_HPP

#include "dom/iterators/abstract_iterator.hpp"
namespace dom::node_iterators {class tree_walker;}

#include "dom/iterators/tree_walker_private.hpp"


class dom::node_iterators::tree_walker
        : public abstract_iterator
{
public constructors:
    tree_walker();

    MAKE_PIMPL(tree_walker);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto parent_node() -> nodes::node*;
    auto first_child() -> nodes::node*;
    auto last_child() -> nodes::node*;
    auto next_sibling() -> nodes::node*;
    auto prev_sibling() -> nodes::node*;
    auto next_node() -> nodes::node*;
    auto prev_node() -> nodes::node*;

public js_properties:
    DEFINE_GETTER(current_node, nodes::node*) {return d_ptr->current;}
    DEFINE_SETTER(current_node, nodes::node*) {d_ptr->current = new_current_node;}
};


#endif //SBROWSER2_TREE_WALKER_HPP
