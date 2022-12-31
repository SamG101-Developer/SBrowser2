module;
#include "ext/macros.hpp"


export module apis.dom.tree_walker:p;
import apis.dom.abstract_iterator;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, tree_walker)
        : dom::abstract_iterator_private
{
public:
    MAKE_QIMPL(tree_walker);
    enum class traversal_child_t {FIRST_CHILD, LAST_CHILD};
    enum class traversal_sibling_t {NEXT_SIBLING, PREVIOUS_SIBLING};

public:
    std::observer_ptr<node> current;

public:
    auto traverse_children(traversal_child_t type) const -> node*;
    auto traverse_siblings(traversal_sibling_t type) const -> node*;
};
