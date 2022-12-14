module;
#include "ext/macros/pimpl.hpp"


export module apis.web_audio.channel_merger_node_private;
import apis.web_audio.audio_node_private;


DEFINE_PRIVATE_CLASS(web_audio, channel_merger_node)
        : web_audio::audio_node_private
{
public:
    MAKE_QIMPL(channel_merger_node);
};