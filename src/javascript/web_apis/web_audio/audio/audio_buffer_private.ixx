module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.audio_buffer_private;
import apis.dom_object_private;

import ext.number;
import ext.string;


DEFINE_PRIVATE_CLASS(web_audio, audio_buffer)
        : dom_object_private
{
public:
    MAKE_QIMPL(audio_buffer);

public:
    auto acquire_contents() -> ext::string;

public:
    ext::number<ulong> number_of_channels;
    ext::number<ulong> length;
    ext::number<float> sample_rate;
    ext::string internal_data; // TODO : type (DataBlock?)
};