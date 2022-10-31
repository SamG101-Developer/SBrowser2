#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_NODE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include "ext/memory.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class document;}


DEFINE_PRIVATE_CLASS(dom::nodes, node) : event_target_private
{
    ext::vector<std::unique_ptr<detail::registered_observer_t>> registered_observer_list;
    std::observer_ptr<dom::nodes::document> node_document;

    ext::vector<std::unique_ptr<node>> child_nodes;
    std::observer_ptr<node> parent_node;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_NODE_PRIVATE_HPP
