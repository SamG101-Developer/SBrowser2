module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.shadow_root_private;
import apis.dom.document_fragment_private;
import apis.dom.mixins.document_or_shadow_root_private;

import apis.dom.types;
import ext.boolean;


DEFINE_PRIVATE_CLASS(dom, shadow_root) final
        : dom::document_fragment_private
        , dom::document_or_shadow_root_private
{
    MAKE_QIMPL(shadow_root);

    detail::shadow_root_mode_t mode;
    detail::slot_assignment_mode_t slot_assignment;
    ext::boolean delegates_focus;
    ext::boolean available_to_element_internals;
};
