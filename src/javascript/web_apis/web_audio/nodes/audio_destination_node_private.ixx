module;
#include "ext/macros.hpp"


export module apis.web_audio.audio_destination_node:p;
import apis.web_audio.audio_node;


DEFINE_PRIVATE_CLASS(web_audio, audio_destination_node)
        : web_audio::audio_node_private
{
public:
    MAKE_QIMPL(audio_destination_node);
};