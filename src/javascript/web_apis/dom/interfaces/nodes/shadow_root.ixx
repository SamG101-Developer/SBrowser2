module;
#include "ext/macros.hpp"


export module apis.dom.shadow_root;
import apis.dom.document_fragment;
import apis.dom.mixins.document_or_shadow_root;
import apis.dom_parsing.mixins.inner_html;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, shadow_root) final
        : public dom::document_fragment
        , public dom::document_or_shadow_root
        , public dom_parsing::inner_html
{
public friends:
    friend class dom::element;

public constructors:
    shadow_root();
    MAKE_PIMPL(shadow_root);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(host, dom::element*);
    DEFINE_GETTER(mode, detail::shadow_root_mode_t);
    DEFINE_GETTER(slot_assignment, detail::slot_assignment_mode_t);
    DEFINE_GETTER(delegates_focus, ext::boolean);
};
