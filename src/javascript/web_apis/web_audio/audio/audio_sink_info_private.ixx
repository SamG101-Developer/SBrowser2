module;
#include "ext/macros/pimpl.hpp"


export module apis.web_audio.audio_sink_info_private;
import apis._.dom_object_private;
import apis.web_audio.types;


DEFINE_PRIVATE_CLASS(web_audio, audio_sink_info)
        : dom_object_private
{
public:
    MAKE_QIMPL(audio_sink_info);

public:
    detail::audio_sink_type_t type;
};