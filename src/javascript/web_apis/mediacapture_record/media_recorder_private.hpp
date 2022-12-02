#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(mediacapture_record)
#include "ext/memory.ixx"
namespace mediacapture::main {class media_stream;}


DEFINE_PRIVATE_CLASS(mediacapture::record, media_recorder) : dom::nodes::event_target_private
{
    std::observer_ptr<main::media_stream> stream;
    ext::string mime_type;
    detail::recording_state_t state;
    ext::number<ulong> video_bits_per_second;
    ext::number<ulong> audio_bits_per_second;
    detail::bitrate_mode_t audio_bitrate_mode;

    ext::string constrained_mime_type;
    ext::number<ulong> constrained_bits_per_second;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_MEDIA_RECORDER_PRIVATE_HPP
