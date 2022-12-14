module;
#include "ext/macros/pimpl.hpp"


export module apis.web_audio.audio_params_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(web_audio, audio_param)
        : dom_object_private
{
public:
    MAKE_QIMPL(audio_param);
};