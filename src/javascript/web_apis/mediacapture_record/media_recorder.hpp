#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_HPP

#include "dom/nodes/event_target.hpp"
namespace mediacapture::record {class media_recorder;}

#include USE_INNER_TYPES(mediacapture_record)
namespace mediacapture::main {class media_stream;}


class mediacapture::record::media_recorder
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(media_recorder);
    media_recorder() = default;
    media_recorder(main::media_stream* stream_option, detail::media_recorder_options&& options = {});

public js_methods:
    static auto is_type_supported(ext::string_view type) -> ext::boolean;

    auto start(ext::number<ulong> timeslice = 0) -> void;
    auto stop() -> void;
    auto pause() -> void;
    auto resume() -> void;
    auto request_data() -> void;

public js_properties:
    ext::property<std::unique_ptr<main::media_stream>> stream;
    ext::property<ext::string> mime_type;
    ext::property<detail::recording_state_t> state;
    ext::property<ext::number<ulong>> video_bits_per_second;
    ext::property<ext::number<ulong>> audio_bits_per_second;
    ext::property<detail::bitrate_mode_t> audio_bitrate_mode;

private js_slots:
    ext::slot<ext::string> s_constrained_mime_type;
    ext::slot<ext::number<ulong>> s_constrained_bits_per_second;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_HPP
