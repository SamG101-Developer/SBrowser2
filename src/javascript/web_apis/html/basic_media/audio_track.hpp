#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP

#include "html/basic_media/abstract_track.hpp"
namespace html::basic_media {class audio_track;}
namespace html::basic_media {class audio_track_private;}

namespace media::source {class source_buffer;}


class html::basic_media::audio_track
        : public abstract_track
{
public constructors:
    audio_track();
    MAKE_PIMPL(audio_track);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(enabled, ext::boolean);
    DEFINE_SETTER(enabled, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP
