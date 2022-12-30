module;
#include "ext/macros.hpp"


export module apis.web_audio.biquad_filter_node:p;
import apis.web_audio.audio_node;


DEFINE_PRIVATE_CLASS(web_audio, biquad_filter_node)
        : web_audio::audio_node_private
{
public:
    MAKE_QIMPL(biquad_filter_node);
};