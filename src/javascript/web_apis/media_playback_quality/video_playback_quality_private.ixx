module;
#include "ext/macros.hpp"


export module apis.media_playback_quality.video_playback_quality:p;
import apis.dom_object;
import apis.hr_time.types;


DEFINE_PRIVATE_CLASS(media_playback_quality, video_playback_quality) : virtual dom_object_private
{
    hr_time::dom_high_res_time_stamp creation_time;
    ext::number<ulong> dropped_video_frames;
    ext::number<ulong> total_video_frames;
};
