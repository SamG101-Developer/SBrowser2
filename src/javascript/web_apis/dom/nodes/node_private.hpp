#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_NODE_PRIVATE_HPP

#include "dom/nodes/event_target_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class document;}


DEFINE_PRIVATE_CLASS(dom::nodes, node) : event_target_private
{
    ext::vector<std::unique_ptr<detail::registered_observer_t>> registered_observer_list;
    dom::nodes::document* node_document;

    ext::vector<std::unique_ptr<node>> child_nodes;
    node* parent_node;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_NODE_PRIVATE_HPP
