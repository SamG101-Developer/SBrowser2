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

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

public js_properties:
    ext::property<std::unique_ptr<nodes::node>> current_node;
};


#endif //SBROWSER2_TREE_WALKER_HPP
