module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.web_audio.audio_render_capacity;
import apis.web_audio.audio_render_capacity_private;

import apis.dom.event_target;

import ext.tuple;
import js.env.module_type;


web_audio::audio_render_capacity::audio_render_capacity()
{
    INIT_PIMPL; ACCESS_PIMPL;
}


auto web_audio::audio_render_capacity::start(audio_render_capacity_options_t&& options) -> void
{
    ACCESS_PIMPL;
    d->event_firing_timer.start(options[u"updateInterval"].to<double>() * 1000);
}


auto web_audio::audio_render_capacity::stop() -> void
{
    ACCESS_PIMPL;
    d->event_firing_timer.stop();
}


auto web_audio::audio_render_capacity::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .function("start", &audio_render_capacity::start)
        .function("stop", &audio_render_capacity::stop)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
