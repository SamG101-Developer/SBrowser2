#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_SHADOW_ROOT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_SHADOW_ROOT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/document_fragment_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class element;}


DEFINE_PRIVATE_CLASS(dom::nodes, shadow_root)
        : document_fragment_private
        , mixins::document_or_shadow_root_private
{
    MAKE_QIMPL(shadow_root);

    detail::shadow_root_mode_t mode;
    detail::slot_assignment_mode_t slot_assignment;
    ext::boolean delegates_focus;
    ext::boolean available_to_element_internals;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_SHADOW_ROOT_PRIVATE_HPP
