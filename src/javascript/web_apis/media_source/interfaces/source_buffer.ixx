module;
#include "ext/macros.hpp"


export module apis.media_source.source_buffer;
import apis.dom.event_target;
import apis.media_source.types;

import ext.js;


DEFINE_PUBLIC_CLASS(media_source, source_buffer) final
        : public dom::event_target
{
public friends:
    friend class media_source;

public constructors:
    DOM_CTORS(source_buffer);
    MAKE_PIMPL(source_buffer);
    MAKE_V8_AVAILABLE(WINDOW | DEDICATED_WORKER);

private js_methods:
    auto append_buffer(ext::buffer_source& data) -> void;
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
