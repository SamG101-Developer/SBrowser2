#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_DOCUMENT_OR_ELEMENT_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_DOCUMENT_OR_ELEMENT_NODE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(dom::mixins, document_or_element_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(document_or_element_node);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_DOCUMENT_OR_ELEMENT_NODE_PRIVATE_HPP
