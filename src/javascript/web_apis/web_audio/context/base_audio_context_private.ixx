module;
#include "ext/macros/pimpl.hpp"


export module apis.web_audio.base_audio_context_private;
import apis.dom.event_target_private;


DEFINE_PRIVATE_CLASS(web_audio, base_audio_context)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(base_audio_context);
};
