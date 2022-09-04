#include "interaction_counts.hpp"


auto event_timing::interaction_counts::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<interaction_counts>{isolate}
        .inherit<dom_object>()
        .inherit<ext::map_like_linked<ext::string, ext::number<ulonglong>>>()
        .auto_wrap_objects();
}
