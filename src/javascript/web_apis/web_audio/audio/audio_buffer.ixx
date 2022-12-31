module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_buffer;
import apis.dom_object;

import ext.any;
import ext.array_buffer;
import ext.map;
import ext.number;
import ext.string;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(web_audio, audio_buffer)
        : public dom_object
{
public typedefs:
    using audio_buffer_options_t = ext::map<ext::string, ext::any>;

public constructors:
    audio_buffer(audio_buffer_options_t&& options = {});
    MAKE_PIMPL(audio_buffer);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto get_channel_data(ext::number<ulong> channel) -> ext::float32_array;
    auto copy_from_channel(ext::float32_array& destination, ext::number<ulong> channel_number, ext::number<ulong> buffer_offset = 0) -> void;
    auto copy_to_channel(const ext::float32_array& source, ext::number<ulong> channel_number, ext::number<ulong> buffer_offset = 0) -> void;

public js_properties:
    DEFINE_GETTER(sample_rate, ext::number<float>);
    DEFINE_GETTER(length, ext::number<ulong>);
    DEFINE_GETTER(duration, ext::number<double>);
    DEFINE_GETTER(number_of_channels, ext::number<ulong>);
};
