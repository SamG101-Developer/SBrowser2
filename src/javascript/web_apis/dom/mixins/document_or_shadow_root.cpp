#include "document_or_shadow_root.hpp"
#include "document_or_shadow_root_private.hpp"


auto dom::mixins::document_or_shadow_root::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document_or_shadow_root>{isolate}
        .inherit<dom_object>()
        // TODO
        .auto_wrap_objects();

    return std::move(conversion);
}
