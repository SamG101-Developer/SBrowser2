#pragma once
#ifndef SBROWSER2_NODE_ITERATOR_HPP
#define SBROWSER2_NODE_ITERATOR_HPP

#include "dom/iterators/abstract_iterator.hpp"
namespace dom::node_iterators {class node_iterator;}

#include "ext/vector.hpp"
namespace dom::nodes {class node;}


class dom::node_iterators::node_iterator
        : public abstract_iterator
{
public constructors:
    DOM_CTORS(node_iterator);
    node_iterator();

public js_methods:
    auto next_node() -> nodes::node*;
    auto prev_node() -> nodes::node*;

public js_properties:
    ext::property<std::unique_ptr<nodes::node>> reference_node;
    ext::property<ext::boolean> pointer_before_reference_node;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    ext::vector<nodes::node*> iterator_collection;
};


#endif //SBROWSER2_NODE_ITERATOR_HPP
