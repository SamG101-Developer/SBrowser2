module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.non_element_parent_node_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(dom, non_element_parent_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(non_element_parent_node);
};
