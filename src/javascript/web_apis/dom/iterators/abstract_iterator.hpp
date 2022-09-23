#pragma once
#ifndef SBROWSER2_ABSTRACT_ITERATOR_HPP
#define SBROWSER2_ABSTRACT_ITERATOR_HPP

#include "dom_object.hpp"
namespace dom::node_iterators {class abstract_iterator;}

#include INCLUDE_INNER_TYPES(dom)
namespace dom::node_iterators {class node_filter;}
namespace dom::nodes {class node;}

#include "dom/iterators/abstract_iterator_private.hpp"


class dom::node_iterators::abstract_iterator
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(abstract_iterator);
    MAKE_PIMPL(abstract_iterator);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(filter, node_filter*) {return d_ptr->filter.get();}
    DEFINE_GETTER(root, nodes::node*) {return d_ptr->root;}
    DEFINE_GETTER(what_to_show, ext::number<ulong>) {return d_ptr->what_to_show;}
};


#endif //SBROWSER2_ABSTRACT_ITERATOR_HPP
