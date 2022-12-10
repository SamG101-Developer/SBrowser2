module;
#include "ext/macros/pimpl.hpp"


module apis.dom.tree_walker_private;
import apis.dom.abstract_iterator_private;
import ext.memory;

namespace dom {class node;}


DEFINE_PRIVATE_CLASS(dom, tree_walker)
        : dom::abstract_iterator_private
{
    MAKE_QIMPL(tree_walker);

    std::observer_ptr<node> current;

    auto traverse_children(traversal_child_t type) const -> node*;
    auto traverse_siblings(traversal_sibling_t type) const -> node*;
};
