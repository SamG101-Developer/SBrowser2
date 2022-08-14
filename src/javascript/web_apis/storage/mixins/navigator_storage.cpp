#include "navigator_storage.hpp"
#include "dom_object.hpp"


auto storage::mixins::navigator_storage::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<navigator_storage>{isolate}
            .inherit<dom_object>()
            .var("storage", &navigator_storage::storage, true)
            .auto_wrap_objects();
}
