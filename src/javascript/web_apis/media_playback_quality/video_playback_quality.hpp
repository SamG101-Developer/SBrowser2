#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP

#include "dom_object.hpp"
namespace media::playback_quality {class video_playback_quality;}

#include USE_INNER_TYPES(high_resolution_time)


class media::playback_quality::video_playback_quality
{
public constructors:
    video_playback_quality() = default;

public js_properties:
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> creation_time;
    ext::property<ext::number<ulong>> dropped_video_frames;
    ext::property<ext::number<ulong>> total_video_frames;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP
