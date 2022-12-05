#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(hr_time)


DEFINE_PRIVATE_CLASS(media::playback_quality, video_playback_quality) : virtual dom_object_private
{
    hr_time::dom_high_res_time_stamp creation_time;
    ext::number<ulong> dropped_video_frames;
    ext::number<ulong> total_video_frames;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_PRIVATE_HPP
