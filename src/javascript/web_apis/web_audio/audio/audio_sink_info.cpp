module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.web_audio.audio_sink_info;
import apis.web_audio.audio_sink_info_private;
import apis.web_audio.types;

import ext.tuple;
import js.env.module_type;


web_audio::audio_sink_info::audio_sink_info()
{
    INIT_PIMPL;
}


auto web_audio::audio_sink_info::get_type() const -> detail::audio_sink_type_t
{
    ACCESS_PIMPL;
    return d->type;
}


auto web_audio::audio_sink_info::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("type", &audio_sink_info::get_type)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
