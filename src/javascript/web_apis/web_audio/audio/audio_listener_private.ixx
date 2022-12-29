module;
#include "ext/macros/macros.hpp"


export module apis.web_audio.audio_listener_private;
import apis.dom_object_private;

namespace web_audio {class audio_param;}


DEFINE_PRIVATE_CLASS(web_audio, audio_listener)
        : dom_object_private
{
public:
    MAKE_QIMPL(audio_listener);

public:
    std::unique_ptr<audio_param> position_x;
    std::unique_ptr<audio_param> position_y;
    std::unique_ptr<audio_param> position_z;

    std::unique_ptr<audio_param> forward_x;
    std::unique_ptr<audio_param> forward_y;
    std::unique_ptr<audio_param> forward_z;

    std::unique_ptr<audio_param> up_x;
    std::unique_ptr<audio_param> up_y;
    std::unique_ptr<audio_param> up_z;
};