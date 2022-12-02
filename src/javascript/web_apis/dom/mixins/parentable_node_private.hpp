#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_PARENTABLE_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_PARENTABLE_NODE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/casting.ixx"
#include "ext/ranges.hpp"
#include <memory>
#include <range/v3/view/transform.hpp>


DEFINE_PRIVATE_CLASS(dom::mixins, parentable_node)
        : virtual dom_object_private
{
    ranges::any_helpful_view<nodes::element*> children = ext::cross_cast<nodes::node_private*>(this)->child_nodes
            | ranges::views::transform(&std::unique_ptr<nodes::node>::get)
            | ranges::views::cast<nodes::element*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_PARENTABLE_NODE_PRIVATE_HPP
