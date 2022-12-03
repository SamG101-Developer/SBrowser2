#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_CHILD_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_CHILD_NODE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(dom::mixins, child_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(child_node);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_CHILD_NODE_PRIVATE_HPP
