#include "cdata_section.hpp"


auto dom::nodes::cdata_section::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<cdata_section>{isolate}
            .inherit<text>()
            .auto_wrap_objects();
}
