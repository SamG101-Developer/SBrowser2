module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.offline_audio_context_private;
import apis.web_audio.base_audio_context_private;


DEFINE_PRIVATE_CLASS(web_audio, offline_audio_context)
        : web_audio::base_audio_context_private
{
public:
    MAKE_QIMPL(offline_audio_context);
};