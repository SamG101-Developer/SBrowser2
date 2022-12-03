#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP

#include "html/basic_media/abstract_track.hpp"
namespace html::basic_media {class text_track;}
namespace html::basic_media {class text_track_private;}

#include INCLUDE_INNER_TYPES(html)

namespace html::basic_media {class text_track_cue;}
namespace media::source {class source_buffer;}


class html::basic_media::text_track
        : public abstract_track
{
public constructors:
    text_track();
    MAKE_PIMPL(text_track);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto add_cue(text_track_cue* cue) -> void;
    auto remove_cue(text_track_cue* cue) -> void;

private js_properties:
    DEFINE_GETTER(in_band_metadata_track_dispatch_type, ext::string_view);
    DEFINE_GETTER(mode, detail::track_mode_t);
    DEFINE_GETTER(cues, ranges::any_helpful_view<text_track_cue*>);
    DEFINE_GETTER(active_cues, ranges::any_helpful_view<text_track_cue*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP
