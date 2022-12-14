module;
#include "ext/macros/pimpl.hpp"


export module apis.web_audio.audio_node_private;
import apis.dom.event_target_private;


DEFINE_PRIVATE_CLASS(web_audio, audio_node)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(audio_node);
};