module;
#include "ext/macros.hpp"


module apis.web_audio.audio_context;
import apis.web_audio.base_audio_context;

import ext.tuple;
import js.env.module_type;


auto web_audio::audio_context::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<base_audio_context>()
        .ctor<audio_context_options_t&&>()
        .function("getOutputTimestamp", &audio_context::get_output_timestamp)
        .function("resume", &audio_context::resume)
        .function("suspend", &audio_context::suspend)
        .function("close", &audio_context::close)
        .function("createMediaElementSource", &audio_context::create_media_element_source)
        .function("createMediaStreamSource", &audio_context::create_media_stream_source)
        .function("createMediaStreamTrackSource", &audio_context::create_media_stream_track_source)
        .function("createMediaStreamDestination", &audio_context::create_media_stream_destination)
        .property("baseLatency", &audio_context::get_base_latency)
        .property("outputLatency", &audio_context::get_output_latency)
        .auto_wrap_objects();

    V8_INTEROP_EXTEND_JS_OBJECT(SECURE)
        .property("sinkId", &audio_context::get_sink_id)
        .property("renderCapacity", &audio_context::get_render_capacity)
        .function("setSinkId", &audio_context::set_sink_id);

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
