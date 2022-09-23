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
    audio_track() = default;

private js_properties:
    ext::property<ext::boolean> enabled;

    /* MEDIA_SOURCE */
    ext::property<std::unique_ptr<media::source::source_buffer>> source_buffer;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private js_properties:
    DEFINE_CUSTOM_GETTER(source_buffer);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MEDIA_AUDIO_TRACK_HPP
