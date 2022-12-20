module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.document_or_element_node_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(dom, document_or_element_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(document_or_element_node);
};

