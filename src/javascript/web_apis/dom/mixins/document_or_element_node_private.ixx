module;
#include "ext/macros.hpp"


export module apis.dom.mixins.document_or_element_node:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom::mixins, document_or_element_node)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(document_or_element_node);
};

