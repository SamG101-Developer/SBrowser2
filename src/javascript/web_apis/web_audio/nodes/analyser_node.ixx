module;
#include "ext/macros.hpp""


export module apis.web_audio.analyser_node;
import apis.web_audio.audio_node;

import ext.any;
import ext.array_buffer;
import ext.map;
import ext.number;
import ext.string;
import ext.tuple;
import ext.type_traits;

import js.env.module_type;

namespace web_audio {class base_audio_context;}


DEFINE_PUBLIC_CLASS(web_audio, analyser_node)
        : public web_audio::audio_node
{
public typedefs:
    using analyser_options_t = ext::map<ext::string, ext::any>;

public constructors:
    analyser_node(base_audio_context* context, analyser_options_t&& options = {});
    DOM_CTORS(analyser_node);
    MAKE_PIMPL(analyser_node);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto get_float_frequency_data(ext::float32_array& array) -> void;
    auto get_byte_frequency_data(ext::uint8_array& array) -> void;
    auto get_float_time_domain_data(ext::float32_array& array) -> void;
    auto get_byte_time_domain_data(ext::uint8_array& array) -> void;

public js_properties:
    DEFINE_GETTER(frequency_bin_count, ext::number<ulong>);

    DEFINE_GETTER(fft_size, ext::number<ulong>);
    DEFINE_GETTER(min_decibels, ext::number<double>);
    DEFINE_GETTER(max_decibels, ext::number<double>);
    DEFINE_GETTER(smoothing_time_constant, ext::number<double>);

    DEFINE_SETTER(fft_size, ext::number<ulong>);
    DEFINE_SETTER(min_decibels, ext::number<double>);
    DEFINE_SETTER(max_decibels, ext::number<double>);
    DEFINE_SETTER(smoothing_time_constant, ext::number<double>);
};
