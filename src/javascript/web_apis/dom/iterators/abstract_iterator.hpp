#pragma once
#ifndef SBROWSER2_ABSTRACT_ITERATOR_HPP
#define SBROWSER2_ABSTRACT_ITERATOR_HPP

#include "dom_object.hpp"
namespace dom::node_iterators {class abstract_iterator;}
namespace dom::node_iterators {class abstract_iterator_private;}

#include INCLUDE_INNER_TYPES(dom)
namespace dom::node_iterators {class node_filter;}
namespace dom::nodes {class node;}


class dom::node_iterators::abstract_iterator
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(abstract_iterator);
    MAKE_PIMPL(abstract_iterator);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(filter, node_filter*);
    DEFINE_GETTER(root, nodes::node*);
    DEFINE_GETTER(what_to_show, ext::number<ulong>);
};


#endif //SBROWSER2_ABSTRACT_ITERATOR_HPP
