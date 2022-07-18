#include "document_or_shadow_root.hpp"


auto dom::mixins::document_or_shadow_root::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<document_or_shadow_root>{isolate}
        .inherit<dom_object>()
        .auto_wrap_objects();
}
