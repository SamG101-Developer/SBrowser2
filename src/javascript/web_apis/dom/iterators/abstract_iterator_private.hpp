#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_ABSTRACT_ITERATOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_ABSTRACT_ITERATOR_PRIVATE_HPP

#include "dom_object_private"
#include "ext/pimpl.hpp"

#include "ext/boolean.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::node_iterators, abstract_iterator) : virtual dom_object_private
{
    ext::boolean active_flag;

    dom::nodes::node* root;
    ext::number<ulong> what_to_show;
    std::unique_ptr<node_filter> filter;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_ABSTRACT_ITERATOR_PRIVATE_HPP
