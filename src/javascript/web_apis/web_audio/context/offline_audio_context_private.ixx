module;
#include "ext/macros.hpp"


export module apis.web_audio.offline_audio_context:p;
import apis.web_audio.base_audio_context;


DEFINE_PRIVATE_CLASS(web_audio, offline_audio_context)
        : web_audio::base_audio_context_private
{
public:
    MAKE_QIMPL(offline_audio_context);
};