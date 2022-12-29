module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.analyser_node_private;
import apis.web_audio.audio_node_private;


DEFINE_PRIVATE_CLASS(web_audio, analyser_node)
        : web_audio::audio_node_private
{
public:
    MAKE_QIMPL(analyser_node);
};