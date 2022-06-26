#ifndef SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP
#define SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {class document_or_shadow_root;}

class dom::mixins::document_or_shadow_root
        : public virtual web_apis::dom_object
{
public constructors:
    document_or_shadow_root();

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP
