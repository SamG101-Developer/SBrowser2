#ifndef SBROWSER2_SHADOW_ROOT_HPP
#define SBROWSER2_SHADOW_ROOT_HPP

#include "dom/nodes/document_fragment.hpp"
#include "dom/mixins/document_or_shadow_root.hpp"
namespace dom::nodes {class shadow_root;}

namespace dom::nodes {class element;}


class dom::nodes::shadow_root final
        : public document_fragment
        , public mixins::document_or_shadow_root
{
public constructors:
    shadow_root();

public js_properties:
    ext::property<std::unique_ptr<element>> host;
    ext::property<ext::string> mode;
    ext::property<ext::string> slot_assignment;
    ext::property<ext::boolean> delegates_focus;

private cpp_members:
    MAKE_PIMPL(shadow_root);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SHADOW_ROOT_HPP
