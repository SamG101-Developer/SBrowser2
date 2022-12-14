module;
#include "ext/macros/pimpl.hpp"


export module apis.web_audio.audio_listener_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(web_audio, audio_listener)
        : dom_object_private
{
public:
    MAKE_QIMPL(audio_listener);
};