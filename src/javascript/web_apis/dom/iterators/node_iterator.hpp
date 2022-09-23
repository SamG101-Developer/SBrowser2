#pragma once
#ifndef SBROWSER2_NODE_ITERATOR_HPP
#define SBROWSER2_NODE_ITERATOR_HPP

#include "dom/iterators/abstract_iterator.hpp"
namespace dom::node_iterators {class node_iterator;}

#include "ext/vector.hpp"
namespace dom::nodes {class node;}

#include "dom/iterators/node_iterator_private.hpp"


class dom::node_iterators::node_iterator
        : public abstract_iterator
{
public constructors:
    node_iterator();
    MAKE_PIMPL(node_iterator);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto next_node() -> nodes::node*;
    auto prev_node() -> nodes::node*;

private js_properties:
    DEFINE_GETTER(reference_node, nodes::node*) {return d_ptr->reference;}
    DEFINE_GETTER(pointer_before_reference_node, ext::boolean) {return d_ptr->pointer_before_reference;}
};


#endif //SBROWSER2_NODE_ITERATOR_HPP
