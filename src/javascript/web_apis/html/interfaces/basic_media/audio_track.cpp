module;
#include "ext/macros.hpp"


module apis.html.audio_track;
import apis.html.abstract_track;

import ext.boolean;
import ext.tuple;
import ext.type_traits;
import js.env.module_type;


auto html::audio_track::get_enabled() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->enabled;
}


auto html::audio_track::set_enabled(ext::boolean new_enabled) -> ext::view_of_t<ext::boolean>
{
    ACCESS_PIMPL;
    return d->enabled = new_enabled;
}


auto html::audio_track::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<abstract_track>()
        .property("enabled", &audio_track::get_enabled, &audio_track::set_enabled)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
