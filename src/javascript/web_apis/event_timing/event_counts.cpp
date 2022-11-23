#include "event_counts.hpp"
#include "event_counts_private.hpp"


event_timing::event_counts::event_counts()
{
    INIT_PIMPL(event_counts);
}


auto event_timing::event_counts::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .inherit<ext::map_like_linked<ext::string, ext::number<ulonglong>>>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
