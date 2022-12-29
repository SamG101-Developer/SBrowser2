module;
#include "ext/macros/macros.hpp"


export module apis.dom.node_iterator_private;
import apis.dom.abstract_iterator_private;

import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, node_iterator)
        : dom::abstract_iterator_private
{
public:
    MAKE_QIMPL(node_iterator);
    enum class traversal_direction_t {NEXT, PREVIOUS};

public:
    auto traverse(traversal_direction_t direction) const -> node*;

    ext::vector<node*> iterator_collection;
    std::observer_ptr<node> reference;
    ext::boolean pointer_before_reference;
};
