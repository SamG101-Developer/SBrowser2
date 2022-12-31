module;
#include "ext/macros.hpp"


export module apis.dom.mixins.parentable_node:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom::mixins, parentable_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(parentable_node);
    parentable_node();

public:
    ranges::any_helpful_view<element*> children;
};
