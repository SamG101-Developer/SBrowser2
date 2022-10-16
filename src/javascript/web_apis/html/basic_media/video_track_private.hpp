#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/basic_media/abstract_track_private.hpp"


DEFINE_PRIVATE_CLASS(html::basic_media, video_track) : html::basic_media::abstract_track_private
{
    ext::boolean selected;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_VIDEO_TRACK_PRIVATE_HPP
