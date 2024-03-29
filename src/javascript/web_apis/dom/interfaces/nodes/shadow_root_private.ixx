module;
#include "ext/macros.hpp"


export module apis.dom.shadow_root:p;
import apis.dom.document_fragment;
import apis.dom.mixins.document_or_shadow_root;
import apis.dom_parsing.mixins.inner_html;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, shadow_root) final
        : dom::document_fragment_private
        , dom::document_or_shadow_root_private
        , dom_parsing::inner_html_private
{
public:
    MAKE_QIMPL(shadow_root);

public:
    detail::shadow_root_mode_t mode;
    detail::slot_assignment_mode_t slot_assignment;
    ext::boolean delegates_focus;
    ext::boolean available_to_element_internals;
};
