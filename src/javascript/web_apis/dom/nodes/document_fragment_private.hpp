#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_FRAGMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_FRAGMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/mixins/non_element_parent_node_private.hpp"
#include "dom/mixins/parentable_node_private.hpp"

namespace dom::nodes {class element;}


DEFINE_PRIVATE_CLASS(dom::nodes, document_fragment)
        : node_private
        , mixins::non_element_parent_node_private
        , mixins::parentable_node_private
{
    dom::nodes::element* host;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_FRAGMENT_PRIVATE_HPP
