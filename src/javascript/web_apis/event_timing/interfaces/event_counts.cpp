module;
#include "ext/macros.hpp"


module apis.event_timing.event_counts;

import ext.core;
import js.env.module_type;


event_timing::event_counts::event_counts()
{
    INIT_PIMPL;
}


auto event_timing::event_counts::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .inherit<ext::map_like_linked<ext::string, ext::number<ulonglong>>>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
