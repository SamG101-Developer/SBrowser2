module;
#include "ext/macros.hpp"


export module apis.dom.mixins.non_document_type_child_node:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom::mixins, non_document_type_child_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(non_document_type_child_node);
};
