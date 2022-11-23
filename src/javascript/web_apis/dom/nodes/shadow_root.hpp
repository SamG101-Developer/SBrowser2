#ifndef SBROWSER2_SHADOW_ROOT_HPP
#define SBROWSER2_SHADOW_ROOT_HPP

#include "dom/nodes/document_fragment.hpp"
#include "dom/mixins/document_or_shadow_root.hpp"
namespace dom::nodes {class shadow_root;}
namespace dom::nodes {class shadow_root_private;}

#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class element;}


class dom::nodes::shadow_root final
        : public document_fragment
        , public mixins::document_or_shadow_root
{
public friends:
    friend class dom::nodes::element;

public constructors:
    shadow_root();
    MAKE_PIMPL(shadow_root);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(host, dom::nodes::element*);
    DEFINE_GETTER(mode, detail::shadow_root_mode_t);
    DEFINE_GETTER(slot_assignment, detail::slot_assignment_mode_t);
    DEFINE_GETTER(delegates_focus, ext::boolean);
};


#endif //SBROWSER2_SHADOW_ROOT_HPP
