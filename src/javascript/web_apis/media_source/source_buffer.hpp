#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_HPP

#include "dom/nodes/event_target.hpp"
#include USE_INNER_TYPES(media_source)
namespace media::source {class source_buffer;}

namespace html::basic_media {class time_ranges;}
namespace html::basic_media {class audio_track;}
namespace html::basic_media {class video_track;}
namespace html::basic_media {class text_track;}


class media::source::source_buffer
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(source_buffer);
    source_buffer() = default;

public js_properties:
    ext::property<detail::append_mode_t> mode;
    ext::property<ext::boolean> updating;
    ext::property<ext::number<double>> timestamp_offset;

    ext::property<ext::number<double>> append_window_start;
    ext::property<ext::number<double>> append_window_end;

    ext::property<std::unique_ptr<html::basic_media::time_ranges>> buffered;
    ext::property<std::unique_ptr<ext::vector<html::basic_media::audio_track*>>> audio_tracks;
    ext::property<std::unique_ptr<ext::vector<html::basic_media::video_track*>>> video_tracks;
    ext::property<std::unique_ptr<ext::vector<html::basic_media::text_track*>>> text_tracks;

public js_methods:
    auto append_buffer(/* TODO */) -> void;
    auto abort() -> void;
    auto change_type(const ext::string& type) -> void;
    auto remove(ext::number<double> start, ext::number<double> end) -> void;

private js_slots:
    ext::slot<ext::boolean> s_generate_timestamps_flag;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(buffered);

    DEFINE_CUSTOM_SETTER(mode);
    DEFINE_CUSTOM_SETTER(timestamp_offset);
    DEFINE_CUSTOM_SETTER(append_window_start);
    DEFINE_CUSTOM_SETTER(append_window_end);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_SOURCE_BUFFER_HPP
