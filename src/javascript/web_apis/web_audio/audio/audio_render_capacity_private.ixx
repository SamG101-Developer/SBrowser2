module;
#include "ext/macros/macros.hpp"
#include <QtCore/QTimer>


export module apis.web_audio.audio_render_capacity_private;
import apis.dom.event_target_private;


DEFINE_PRIVATE_CLASS(web_audio, audio_render_capacity)
        : dom::event_target_private
{
public:
    audio_render_capacity_private();
    MAKE_QIMPL(audio_render_capacity);

public:
    QTimer event_firing_timer;
};