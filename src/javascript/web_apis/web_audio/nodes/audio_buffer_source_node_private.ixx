module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.audio_buffer_source_node_private;
import apis.web_audio.audio_node_private;


DEFINE_PRIVATE_CLASS(web_audio, audio_buffer_source_node)
        : web_audio::audio_node_private
{
public:
    MAKE_QIMPL(audio_buffer_source_node);
};