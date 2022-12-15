module;
#include "ext/macros/pimpl.hpp"


module apis.web_audio.audio_buffer;
import apis.web_audio.audio_buffer_private;

import ext.number;


auto web_audio::audio_buffer::get_sample_rate() const -> ext::number<float>
{
    ACCESS_PIMPL;
    return d->sample_rate;
}


auto web_audio::audio_buffer::get_length() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->length;
}


auto web_audio::audio_buffer::get_duration() const -> ext::number<double>
{
    ACCESS_PIMPL;
    return d->length / d->sample_rate;
}


auto web_audio::audio_buffer::get_number_of_channels() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->number_of_channels;
}
