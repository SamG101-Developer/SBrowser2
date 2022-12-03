#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_NON_ELEMENT_PARENT_NODE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_NON_ELEMENT_PARENT_NODE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(dom::mixins, non_element_parent_node)
        : virtual dom_object_private
{
    MAKE_QIMPL(non_element_parent_node);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_NON_ELEMENT_PARENT_NODE_PRIVATE_HPP
