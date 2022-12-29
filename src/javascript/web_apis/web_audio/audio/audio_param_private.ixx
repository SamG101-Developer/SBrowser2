module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.audio_param_private;
import apis.dom_object_private;
import apis.web_audio.types;

import ext.number;


DEFINE_PRIVATE_CLASS(web_audio, audio_param)
        : virtual dom_object_private
{
public:
    audio_param_private();
    MAKE_QIMPL(audio_param);

public:
    detail::automation_rate_t automation_rate;
    ext::number<float> default_value;
    ext::number<float> min_value;
    ext::number<float> max_value;
    ext::number<float> value;
};
