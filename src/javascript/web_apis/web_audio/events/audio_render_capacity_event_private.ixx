module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.audio_render_capacity_event_private;
import apis.dom.event_private;

import ext.number;


DEFINE_PRIVATE_CLASS(web_audio, audio_render_capacity_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(audio_render_capacity_event);

public:
    ext::number<double> timestamp;
    ext::number<double> average_load;
    ext::number<double> peak_load;
    ext::number<double> underrun_ratio;
};