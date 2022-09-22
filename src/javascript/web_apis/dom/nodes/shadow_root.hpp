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

public js_properties:
    ext::property<std::unique_ptr<element>> host;
    ext::property<detail::shadow_root_mode_t> mode;
    ext::property<detail::slot_assignment_mode_t> slot_assignment;
    ext::property<ext::boolean> delegates_focus;

private cpp_members:
    MAKE_PIMPL(shadow_root);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(host) {return document_fragment::d_ptr->host;}
    DEFINE_CUSTOM_GETTER(mode) {return d_ptr->mode;}
    DEFINE_CUSTOM_GETTER(slot_assignment) {return d_ptr->slot_assignment;}
    DEFINE_CUSTOM_GETTER(delegates_focus) {return d_ptr->delegates_focus;}
};


#endif //SBROWSER2_SHADOW_ROOT_HPP
