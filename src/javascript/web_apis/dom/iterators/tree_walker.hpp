#pragma once
#ifndef SBROWSER2_TREE_WALKER_HPP
#define SBROWSER2_TREE_WALKER_HPP

#include "dom/iterators/abstract_iterator.hpp"
namespace dom::node_iterators {class tree_walker;}


class dom::node_iterators::tree_walker
        : public abstract_iterator
{
public constructors:
    tree_walker();

public js_methods:
    auto parent_node() -> nodes::node*;
    auto first_child() -> nodes::node*;
    auto last_child() -> nodes::node*;
    auto next_sibling() -> nodes::node*;
    auto prev_sibling() -> nodes::node*;
    auto next_node() -> nodes::node*;
    auto prev_node() -> nodes::node*;

public js_properties:
    ext::property<nodes::node*> current_node;

private cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_TREE_WALKER_HPP
