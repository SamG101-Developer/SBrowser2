#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_TREE_WALKER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_TREE_WALKER_PRIVATE_HPP

#include "dom/iterators/abstract_iterator_private.hpp"

#include "ext/pimpl.hpp"

namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::node_iterators, tree_walker) : abstract_iterator_private
{
    nodes::node* current;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_TREE_WALKER_PRIVATE_HPP
