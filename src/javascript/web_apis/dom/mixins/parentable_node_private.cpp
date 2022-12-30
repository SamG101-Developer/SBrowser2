module;
#include <range/v3/view/transform.hpp>

module apis.dom.parentable_node:p;
import apis.dom.node;

import ext.core;


dom::mixins::parentable_node_private::parentable_node_private()
{
    children = ext::cross_cast<node_private*>(this)->child_nodes
            | ranges::views::transform(ext::underlying)
            | ranges::views::cast<element*>;
}
