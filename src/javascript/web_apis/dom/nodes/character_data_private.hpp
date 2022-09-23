#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CHARACTER_DATA_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CHARACTER_DATA_PRIVATE_HPP

#include "dom/nodes/node_private.hpp"
#include "dom/mixins/child_node_private.hpp"
#include "dom/mixins/non_document_type_child_node_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, character_data)
        : node_private
        , child_node_private
        , non_document_type_child_node_private
{
    ext::string data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CHARACTER_DATA_PRIVATE_HPP
