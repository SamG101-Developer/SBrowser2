#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_ABSTRACT_ITERATOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_ABSTRACT_ITERATOR_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"
#include "ext/vector.hpp"
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::node_iterators, abstract_iterator)
        : virtual dom_object_private
{
    MAKE_QIMPL(abstract_iterator);

    ext::boolean active_flag;

    std::observer_ptr<dom::nodes::node> root;
    ext::number<ulong> what_to_show;
    std::unique_ptr<node_filter> filter;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_ABSTRACT_ITERATOR_PRIVATE_HPP
