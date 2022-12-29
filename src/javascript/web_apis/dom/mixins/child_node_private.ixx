module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.child_node_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(dom::mixins, child_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(child_node);
};
