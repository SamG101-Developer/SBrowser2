#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_NON_DOCUMENT_TYPE_CHILD_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_NON_DOCUMENT_TYPE_CHILD_NODE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(dom::mixins, non_document_type_child_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(non_document_type_child_node);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_NON_DOCUMENT_TYPE_CHILD_NODE_PRIVATE_HPP
