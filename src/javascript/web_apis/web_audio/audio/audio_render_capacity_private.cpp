module;
#include <QtCore/QTimer>


module apis.web_audio.audio_render_capacity:p;


web_audio::audio_render_capacity_private::audio_render_capacity_private()
{
    event_firing_timer.setSingleShot(false);
    QObject::connect(event_firing_timer, &QTimer::timeout, [this] {fire_event(u"update");});
}
