module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.node_iterator_private;
import apis.dom.abstract_iterator_private;
import ext.boolean;
import ext.memory;
import ext.vector;

namespace dom {class node;}


DEFINE_PRIVATE_CLASS(dom, node_iterator)
        : dom::abstract_iterator_private
{
    MAKE_QIMPL(node_iterator);

    ext::vector<node*> iterator_collection;
    std::observer_ptr<node> reference;
    ext::boolean pointer_before_reference;
};
