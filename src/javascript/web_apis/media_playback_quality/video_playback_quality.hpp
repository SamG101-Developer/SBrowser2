#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP

#include "dom_object.hpp"
namespace media::playback_quality {class video_playback_quality;}

#include INCLUDE_INNER_TYPES(hr_time)


class media::playback_quality::video_playback_quality
        : public virtual dom_object
{
public constructors:
    video_playback_quality() = default;

public js_properties:
    ext::property<hr_time::dom_high_res_time_stamp> creation_time;
    ext::property<ext::number<ulong>> dropped_video_frames;
    ext::property<ext::number<ulong>> total_video_frames;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_PLAYBACK_QUALITY_VIDEO_PLAYBACK_QUALITY_HPP
