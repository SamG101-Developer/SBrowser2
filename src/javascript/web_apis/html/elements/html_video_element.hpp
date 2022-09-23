#pragma once
#ifndef SBROWSER2_HTML_VIDEO_ELEMENT_HPP
#define SBROWSER2_HTML_VIDEO_ELEMENT_HPP

#include "html/elements/html_media_element.hpp"
namespace html::elements {class html_video_element;}

namespace media::playback_quality {class video_playback_quality;}


class html::elements::html_video_element
        : public html_media_element
{
public constructors:
    DOM_CTORS(html_video_element);
    html_video_element() = default;

public js_methods:
    /* MEDIA_PLAYBACK_QUALITY*/
    auto get_video_playback_quality() -> media::playback_quality::video_playback_quality;

private js_properties:
    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;
    ext::property<ext::number<ulong>> video_width;
    ext::property<ext::number<ulong>> video_height;
    ext::property<ext::string> poster;
    ext::property<ext::boolean> plays_inline;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    /* MEDIA_PLAYBACK_QUALITY*/
    ext::number<int> m_total_video_frame_count = 0;
    ext::number<int> m_dropped_video_frame_count = 0;

private js_properties:
    DEFINE_CUSTOM_GETTER(video_width);
    DEFINE_CUSTOM_GETTER(video_height);
};


#endif //SBROWSER2_HTML_VIDEO_ELEMENT_HPP
