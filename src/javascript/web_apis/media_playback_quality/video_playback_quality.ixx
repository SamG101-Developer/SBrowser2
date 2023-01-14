module;
#include "ext/macros.hpp"


export module apis.media_playback_quality.video_playback_quality;
import apis.dom_object;
import apis.hr_time.types;


DEFINE_PUBLIC_CLASS(media_playback_quality, video_playback_quality) final
        : public virtual dom_object
{
public constructors:
    video_playback_quality();
    MAKE_PIMPL(video_playback_quality);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(creation_time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(dropped_video_frames, ext::number<ulong>);
    DEFINE_GETTER(total_video_frames, ext::number<ulong>);
};
