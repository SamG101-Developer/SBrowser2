#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP

#include "dom_object.hpp"
namespace media::playback_quality {class video_playback_quality;}
namespace media::playback_quality {class video_playback_quality_private;}

#include INCLUDE_INNER_TYPES(hr_time)


class media::playback_quality::video_playback_quality
        : public virtual dom_object
{
public constructors:
    video_playback_quality();
    MAKE_PIMPL(video_playback_quality);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(creation_time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(dropped_video_frames, ext::number<ulong>);
    DEFINE_GETTER(total_video_frames, ext::number<ulong>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP
