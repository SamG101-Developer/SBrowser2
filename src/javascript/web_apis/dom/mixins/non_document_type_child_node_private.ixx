module;
#include "ext/macros/macros.hpp"


export module apis.dom.mixins.non_document_type_child_node_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(dom::mixins, non_document_type_child_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(non_document_type_child_node);
};
