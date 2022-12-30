module;
#include "ext/macros.hpp"
#include <QtCore/QTimer>


export module apis.web_audio.audio_render_capacity:p;
import apis.dom.event_target;


DEFINE_PRIVATE_CLASS(web_audio, audio_render_capacity)
        : dom::event_target_private
{
public:
    audio_render_capacity_private();
    MAKE_QIMPL(audio_render_capacity);

public:
    QTimer event_firing_timer;
};