module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.biquad_filter_node_private;
import apis.web_audio.audio_node_private;


DEFINE_PRIVATE_CLASS(web_audio, biquad_filter_node)
        : web_audio::audio_node_private
{
public:
    MAKE_QIMPL(biquad_filter_node);
};