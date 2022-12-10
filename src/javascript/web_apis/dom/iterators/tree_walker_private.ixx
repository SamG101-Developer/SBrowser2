module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.tree_walker_private;
import apis.dom.abstract_iterator_private;
import ext.memory;

namespace dom {class node;}


DEFINE_PRIVATE_CLASS(dom, tree_walker)
        : dom::abstract_iterator_private
{
    MAKE_QIMPL(tree_walker);
    enum class traversal_child_t {FIRST_CHILD, LAST_CHILD};
    enum class traversal_sibling_t {NEXT_SIBLING, PREVIOUS_SIBLING};

    std::observer_ptr<node> current;

    auto traverse_children(traversal_child_t type) const -> node*;
    auto traverse_siblings(traversal_sibling_t type) const -> node*;
};
