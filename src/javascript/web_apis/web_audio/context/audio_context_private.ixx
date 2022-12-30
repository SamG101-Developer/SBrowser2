module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_context:p;
import apis.web_audio.base_audio_context;

import ext.boolean;


DEFINE_PRIVATE_CLASS(web_audio, audio_context)
        : web_audio::base_audio_context_private
{
public:
    MAKE_QIMPL(audio_context);

    ext::boolean suspended_by_user;
};