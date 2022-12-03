#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_AUDIO_TRACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_AUDIO_TRACK_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/basic_media/abstract_track_private.hpp"

namespace media::source {class source_buffer;}


DEFINE_PRIVATE_CLASS(html::basic_media, audio_track) : html::basic_media::abstract_track_private
{
    ext::boolean enabled;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_AUDIO_TRACK_PRIVATE_HPP
