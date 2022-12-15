module;
#include <memory>


module apis.web_audio.base_audio_context;
import apis.web_audio.base_audio_context_private;

import apis.web_audio.analyser_node;
import apis.web_audio.biquad_filter_node;

import apis.web_audio.audio_buffer;
import apis.web_audio.audio_buffer_private;

import ext.number;


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
    auto buffer = std::make_unique<array_buffer>();
    buffer->d_func()->number_of_channels = number_of_channels;
    buffer->d_func()->length = lemgth;
    buffer->d_func()->sample_rate = sample_rate;
    return std::move(buffer);
}
