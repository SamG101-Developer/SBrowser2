module;
#include "ext/macros.hpp"

module apis.web_audio.base_audio_context;

import apis.web_audio.analyser_node;
import apis.web_audio.biquad_filter_node;
import apis.web_audio.audio_buffer_source_node;

import apis.web_audio.audio_buffer;

import apis.dom.event_target;

import ext.number;
import ext.tuple;
import js.env.module_type;


auto web_audio::base_audio_context::create_analyser() const -> std::unique_ptr<analyser_node>
{
    return std::make_unique<analyser_node>(this);
}


auto web_audio::base_audio_context::create_biquad_filter() const -> std::unique_ptr<biquad_filter_node>
{
    return std::make_unique<biquad_filter_node>(this);
}


auto web_audio::base_audio_context::create_buffer(
        ext::number <ulong> number_of_channels,
        ext::number <ulong> length,
        ext::number<float> sample_rate)
        const -> std::unique_ptr<audio_buffer>
{
    auto buffer = std::make_unique<audio_buffer>(this);
    buffer->d_func()->number_of_channels = number_of_channels;
    buffer->d_func()->length = length;
    buffer->d_func()->sample_rate = sample_rate;
    return std::move(buffer);
}


auto web_audio::base_audio_context::create_buffer_source() const -> std::unique_ptr<audio_buffer_source_node>
{
    return std::make_unique<audio_buffer_source_node>(this);
}


auto web_audio::base_audio_context::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .function("createAnalyser", &base_audio_context::create_analyser)
        .function("createBiquadFilter", &base_audio_context::create_biquad_filter)
        .function("createBuffer", &base_audio_context::create_buffer)
        .function("createBufferSource", &base_audio_context::create_buffer_source)
        .function("createChannelMerger", &base_audio_context::create_channel_merger)
        .function("createChannelSplitter", &base_audio_context::create_channel_splitter)
        .function("createConstantSource", &base_audio_context::create_constant_source)
        .function("createConvolver", &base_audio_context::create_convolver)
        .function("createDelay", &base_audio_context::create_delay)
        .function("createDynamicCompresor", &base_audio_context::create_dynamic_compressor)
        .function("createGain", &base_audio_context::create_gain)
        .function("createIIRFilter", &base_audio_context::create_iir_filter)
        .function("createOscillator", &base_audio_context::create_oscillator)
        .function("createPanner", &base_audio_context::create_panner)
        .function("createPeriodicWave", &base_audio_context::create_periodic_wave)
        .function("createScriptProcessing", &base_audio_context::create_script_processor)
        .function("createStereoPanner", &base_audio_context::create_stereo_panner)
        .function("createWaveShaper", &base_audio_context::create_wave_shaper)
        .function("decodeAudioData", &base_audio_context::decode_audio_data)
        .property("destination", &base_audio_context::get_destination)
        .property("sampleRate", &base_audio_context::get_sample_rate)
        .property("currentTime", &base_audio_context::get_current_time)
        .property("listener", &base_audio_context::get_listener)
        .property("state", &base_audio_context::get_state)
        .auto_wrap_objects();

    V8_INTEROP_EXTEND_JS_OBJECT(SECURE)
        .property("audioWorlet", &base_audio_context::get_audio_worklet);

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
