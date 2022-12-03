#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_TREE_WALKER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_TREE_WALKER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/iterators/abstract_iterator_private.hpp"

#include "ext/memory.ixx"
namespace dom::nodes {class node;}


DEFINE_PRIVATE_CLASS(dom::node_iterators, tree_walker)
        : abstract_iterator_private
{
    MAKE_QIMPL(tree_walker);

    std::observer_ptr<nodes::node> current;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ITERATORS_TREE_WALKER_PRIVATE_HPP
