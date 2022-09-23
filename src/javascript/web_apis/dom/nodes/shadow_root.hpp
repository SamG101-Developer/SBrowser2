#ifndef SBROWSER2_SHADOW_ROOT_HPP
#define SBROWSER2_SHADOW_ROOT_HPP

#include "dom/nodes/document_fragment.hpp"
#include "dom/mixins/document_or_shadow_root.hpp"
namespace dom::nodes {class shadow_root;}

#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class element;}

#include "dom/nodes/shadow_root_private.hpp"


class dom::nodes::shadow_root final
        : public document_fragment
        , public mixins::document_or_shadow_root
{
public constructors:
    shadow_root();

private cpp_members:
    MAKE_PIMPL(shadow_root);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(host, dom::nodes::element*) {return document_fragment::d_ptr->host;}
    DEFINE_GETTER(mode, detail::shadow_root_mode_t) {return d_ptr->mode;}
    DEFINE_GETTER(slot_assignment, detail::slot_assignment_mode_t) {return d_ptr->slot_assignment;}
    DEFINE_GETTER(delegates_focus, ext::boolean) {return d_ptr->delegates_focus;}
};


#endif //SBROWSER2_SHADOW_ROOT_HPP
