#ifndef SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP
#define SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP

#include "dom_object.hpp"
namespace dom::mixins {class document_or_shadow_root;}

namespace dom::nodes {class element;}

class dom::mixins::document_or_shadow_root
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(document_or_shadow_root);
    document_or_shadow_root() = default;

public js_properties:
    /* HTML */
    ext::property<nodes::element*> active_element;

    /* POINTER_LOCK */
    ext::property<nodes::element*> pointer_lock_element;

    /* FULLSCREEN */
    ext::property<nodes::element*> fullscreen_element;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP
