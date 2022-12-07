module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.non_document_type_child_node_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(dom, non_document_type_child_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(non_document_type_child_node);
};
