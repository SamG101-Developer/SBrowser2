#include "abstract_range.hpp"


auto dom::node_ranges::abstract_range::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<abstract_range>{isolate}
            .inherit<dom_object>()
            .var("collapsed", &abstract_range::collapsed, true)
            .var("startContainer", &abstract_range::start_container, true)
            .var("startOffset", &abstract_range::start_offset, true)
            .var("endContainer", &abstract_range::end_container, true)
            .var("endOffset", &abstract_range::end_offset, true)
            .auto_wrap_objects();
}
