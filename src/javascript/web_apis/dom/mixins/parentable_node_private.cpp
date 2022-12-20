module;
#include <range/v3/view/transform.hpp>

module apis.dom.parentable_node_private;
import apis.dom.node_private;

import ext.core;


dom::mixins::parentable_node_private::parentable_node_private()
{
    children = ext::cross_cast<node_private*>(this)->child_nodes
            | ranges::views::transform(ext::underlying)
            | ranges::views::cast<element*>;
}
