#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_TYPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_TYPE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/node_private.hpp"
#include "dom/mixins/child_node_private.hpp"




DEFINE_PRIVATE_CLASS(dom::nodes, document_type)
        : node_private
        , mixins::child_node_private
{
    MAKE_QIMPL(document_type);

    ext::string name;
    ext::string public_id;
    ext::string system_id;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_TYPE_PRIVATE_HPP
