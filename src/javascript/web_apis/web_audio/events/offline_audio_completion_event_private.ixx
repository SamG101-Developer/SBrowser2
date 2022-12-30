module;
#include "ext/macros.hpp"


export module apis.web_audio.offline_audio_completion_event:p;
import apis.dom.event;

namespace web_audio {class audio_buffer;}


DEFINE_PRIVATE_CLASS(web_audio, offline_audio_completion_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(offline_audio_completion_event);

    std::unique_ptr<audio_buffer> rendered_buffer;
};