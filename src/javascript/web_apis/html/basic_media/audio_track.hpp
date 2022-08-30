#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP

#include "html/basic_media/abstract_track.hpp"
namespace html::basic_media {class audio_track;}

namespace media::source {class source_buffer;}


class html::basic_media::audio_track
        : public abstract_track
{
public constructors:
    DOM_CTORS(audio_track);
    audio_track() = default;

public js_properties:
    ext::property<ext::boolean> enabled;

    ext::property<std::unique_ptr<media::source::source_buffer>> source_buffer;

private cpp_accessors:
    DEFINE_GETTER(source_buffer);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP
