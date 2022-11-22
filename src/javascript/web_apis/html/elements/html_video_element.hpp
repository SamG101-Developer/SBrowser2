#pragma once
#ifndef SBROWSER2_HTML_VIDEO_ELEMENT_HPP
#define SBROWSER2_HTML_VIDEO_ELEMENT_HPP

#include "html/elements/html_media_element.hpp"
namespace html::elements {class html_video_element;}
namespace html::elements {class html_video_element_private;}

namespace media::playback_quality {class video_playback_quality;}


class html::elements::html_video_element
        : public html_media_element
{
public constructors:
    DOM_CTORS(html_video_element);
    MAKE_PIMPL(html_video_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    /* [MEDIA-PLAYBACK-QUALITY] */
    auto get_video_playback_quality() -> std::unique_ptr<media::playback_quality::video_playback_quality>;

private js_properties:
    DEFINE_GETTER(width, ext::number<ulong>);
    DEFINE_GETTER(height, ext::number<ulong>);
    DEFINE_GETTER(video_width, ext::number<ulong>);
    DEFINE_GETTER(video_height, ext::number<ulong>);
    DEFINE_GETTER(poster, ext::string);
    DEFINE_GETTER(plays_inline, ext::boolean);

    DEFINE_SETTER(width, ext::number<ulong>);
    DEFINE_SETTER(height, ext::number<ulong>);
    DEFINE_SETTER(poster, ext::string);
    DEFINE_SETTER(plays_inline, ext::boolean);
};


#endif //SBROWSER2_HTML_VIDEO_ELEMENT_HPP
