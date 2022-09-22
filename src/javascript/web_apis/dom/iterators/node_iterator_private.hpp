#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_NODE_ITERATOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_NODE_ITERATOR_PRIVATE_HPP

#include "ext/boolean.hpp"
#include "ext/pimpl.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::node_iterators, node_iterator)
{
    ext::vector<nodes::node*> iterator_collection;
    dom::nodes::node* reference;
    ext::boolean pointer_before_reference;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_NODE_ITERATOR_PRIVATE_HPP
