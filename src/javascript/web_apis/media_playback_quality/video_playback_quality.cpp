#include "video_playback_quality.hpp"
#include "video_playback_quality_private.hpp"

#include "hr_time/detail/time_internals.hpp"


media::playback_quality::video_playback_quality::video_playback_quality()
{
    INIT_PIMPL(video_playback_quality);
    auto e = js::env::env::current();

    ACCESS_PIMPL(video_playback_quality);
    d->creation_time = hr_time::detail::current_hr_time(e.js.global());
}


auto media::playback_quality::video_playback_quality::get_creation_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const video_playback_quality);
    return d->creation_time;
}


auto media::playback_quality::video_playback_quality::get_dropped_video_frames() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const video_playback_quality);
    return d->dropped_video_frames;
}


auto media::playback_quality::video_playback_quality::get_total_video_frames() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const video_playback_quality);
    return d->total_video_frames;
}


auto media::playback_quality::video_playback_quality::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<video_playback_quality>{isolate}
        .inherit<dom_object>()
        .property("creationTime", &video_playback_quality::get_creation_time)
        .property("droppedVideoFrames", &video_playback_quality::get_dropped_video_frames)
        .property("totalVideoFrames", &video_playback_quality::get_total_video_frames)
        .auto_wrap_objects();

    return std::move(conversion);
}
