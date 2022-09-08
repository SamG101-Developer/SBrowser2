#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_HPP

#include "html/basic_media/abstract_track.hpp"
namespace html::basic_media {class video_track;}


class html::basic_media::video_track
        : public abstract_track
{
public constructors:
    video_track() = default;

public js_properties:
    ext::property<ext::boolean> selected;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_HPP
