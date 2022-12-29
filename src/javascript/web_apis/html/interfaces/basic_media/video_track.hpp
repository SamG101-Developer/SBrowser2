#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_HPP

#include "html/basic_media/abstract_track.hpp"
namespace html::basic_media {class video_track;}
namespace html::basic_media {class video_track_private;}


class html::basic_media::video_track
        : public abstract_track
{
public constructors:
    video_track();
    MAKE_PIMPL(video_track);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(selected, ext::boolean);
    DEFINE_SETTER(selected, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_HPP
