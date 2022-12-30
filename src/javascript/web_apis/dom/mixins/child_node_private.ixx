module;
#include "ext/macros.hpp"


export module apis.dom.mixins.child_node:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom::mixins, child_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(child_node);
};
