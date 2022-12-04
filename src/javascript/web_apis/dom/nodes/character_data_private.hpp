#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CHARACTER_DATA_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CHARACTER_DATA_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/node_private.hpp"
#include "dom/mixins/child_node_private.hpp"
#include "dom/mixins/non_document_type_child_node_private.hpp"




DEFINE_PRIVATE_CLASS(dom::nodes, character_data)
        : node_private
        , mixins::child_node_private
        , mixins::non_document_type_child_node_private
{
    MAKE_QIMPL(character_data);

    ext::string data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CHARACTER_DATA_PRIVATE_HPP
