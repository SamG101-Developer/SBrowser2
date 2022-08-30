#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP

#include "html/basic_media/abstract_track.hpp"
namespace html::basic_media {class text_track;}

#include USE_INNER_TYPES(html)
namespace media::source {class source_buffer;}
namespace html::basic_media {class text_track_cue;}


class html::basic_media::text_track
        : public abstract_track
{
public constructors:
    DOM_CTORS(text_track);
    text_track() = default;

public js_methods:
    auto add_cue(text_track_cue* cue) -> void;
    auto remove_cue(text_track_cue* cue) -> void;

public js_properties:
    ext::property<ext::string> in_band_dispatch_type;
    ext::property<detail::track_readiness_state_t> readiness_state;
    ext::property<detail::track_mode_t> mode;

    ext::property<std::unique_ptr<ext::vector<text_track_cue*>>> cues;
    ext::property<std::unique_ptr<ext::vector<text_track_cue*>>> active_cues;

    ext::property<std::unique_ptr<media::source::source_buffer>> source_buffer;

private cpp_properties:
    ext::vector<text_track_cue*> m_text_track_cues;

private cpp_accessors:
    DEFINE_GETTER(source_buffer);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP
