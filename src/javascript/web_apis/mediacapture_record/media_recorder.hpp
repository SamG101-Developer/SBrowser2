#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_HPP

#include "dom/nodes/event_target.hpp"
namespace mediacapture::record {class media_recorder;}
namespace mediacapture::record {class media_recorder_private;}

#include INCLUDE_INNER_TYPES(mediacapture_record)
namespace mediacapture::main {class media_stream;}


class mediacapture::record::media_recorder
        : public dom::nodes::event_target
{
public constructors:
    media_recorder(main::media_stream* stream, detail::media_recorder_options&& options = {});
    DOM_CTORS(media_recorder);
    MAKE_PIMPL(media_recorder);
    MAKE_V8_AVAILABLE;

public js_methods:
    static auto is_type_supported(ext::string_view type) -> ext::boolean;

    auto start(ext::number<ulong> timeslice = 0) -> void;
    auto stop() -> void;
    auto pause() -> void;
    auto resume() -> void;
    auto request_data() -> void;

private js_properties:
    DEFINE_GETTER(stream, main::media_stream*);
    DEFINE_GETTER(mime_type, ext::string_view);
    DEFINE_GETTER(state, detail::recording_state_t);

    DEFINE_GETTER(video_bits_per_second, ext::number<ulong>);
    DEFINE_GETTER(audio_bits_per_second, ext::number<ulong>);
    DEFINE_GETTER(audio_bitrate_mode, detail::bitrate_mode_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_HPP
