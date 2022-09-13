#include "html_video_element.hpp"

#include "hr_time/detail/time_internals.hpp"
#include "media_playback_quality/video_playback_quality.hpp"


auto html::elements::html_video_element::get_video_playback_quality()
        -> media::playback_quality::video_playback_quality
{
    JS_REALM_GET_CURRENT;

    auto playback_quality = media::playback_quality::video_playback_quality{};
    playback_quality.creation_time = hr_time::detail::current_hr_time(current_global_object);
    playback_quality.total_video_frames = m_total_video_frame_count;
    playback_quality.dropped_video_frames = m_dropped_video_frame_count;
    return playback_quality;
}


auto html::elements::html_video_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_video_element>{isolate}
        .ctor<>()
        .var("width", &html_video_element::width, true)
        .var("height", &html_video_element::height, true)
        .var("videoWidth", &html_video_element::width, false)
        .var("videoHeight", &html_video_element::height, false)
        .var("poster", &html_video_element::width, true)
        .var("playsInline", &html_video_element::height, true)
        .auto_wrap_objects();
}
