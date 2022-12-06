#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_HPP


namespace media::source {class source_buffer;}
namespace media::source {class source_buffer_private;}

#include INCLUDE_INNER_TYPES(media_source)
#include INCLUDE_INNER_TYPES(web_idl)

namespace html::basic_media {class time_ranges;}
namespace html::basic_media {class audio_track;}
namespace html::basic_media {class video_track;}
namespace html::basic_media {class text_track;}
namespace media::source {class media_source;}


class media::source::source_buffer
        : public dom::nodes::event_target
{
public friends:
    friend class media_source;

public constructors:
    DOM_CTORS(source_buffer);
    MAKE_PIMPL(source_buffer);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto append_buffer(v8::BufferSource data) -> void;
    auto abort() -> void;
    auto change_type(const ext::string& type) -> void;
    auto remove(ext::number<double> start, ext::number<double> end) -> void;

private js_properties:
    DEFINE_GETTER(mode, detail::append_mode_t);
    DEFINE_GETTER(updating, ext::boolean);
    DEFINE_GETTER(timestamp_offset, ext::number<double>);

    DEFINE_GETTER(append_window_start, ext::number<double>);
    DEFINE_GETTER(append_window_end, ext::number<double>);

    DEFINE_GETTER(buffered, html::basic_media::time_ranges*);
    DEFINE_GETTER(audio_tracks, ranges::any_helpful_view<html::basic_media::audio_track*>);
    DEFINE_GETTER(video_tracks, ranges::any_helpful_view<html::basic_media::video_track*>);
    DEFINE_GETTER(text_tracks, ranges::any_helpful_view<html::basic_media::text_track*>);

    DEFINE_SETTER(mode, detail::append_mode_t);
    DEFINE_SETTER(timestamp_offset, ext::number<double>);
    DEFINE_SETTER(append_window_start, ext::number<double>);
    DEFINE_SETTER(append_window_end, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_HPP
