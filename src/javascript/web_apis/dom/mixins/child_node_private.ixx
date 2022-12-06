module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.child_node;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(dom, child_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(child_node);
};
