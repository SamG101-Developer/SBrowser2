module;
#include "ext/macros.hpp"


export module apis.dom.node_iterator:p;
import apis.dom.abstract_iterator;


IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, node_iterator)
        : dom::abstract_iterator_private
{
public:
    MAKE_QIMPL(node_iterator);
    enum class traversal_direction_t {NEXT, PREVIOUS};

public:
    auto traverse(traversal_direction_t direction) const -> node*;

public:
    ext::vector<node*> iterator_collection;
    std::observer_ptr<node> reference;
    ext::boolean pointer_before_reference;
};
