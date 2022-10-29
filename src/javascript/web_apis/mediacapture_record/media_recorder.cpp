#include "media_recorder.hpp"

#include "ext/ranges.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(mediacapture_record)

#include "dom/detail/exception_internals.hpp"
#include "mediacapture_main/detail/track_internals.hpp"
#include "mediacapture_main/media_stream.hpp"
#include "mediacapture_main/media_stream_track.hpp"


mediacapture::record::media_recorder::media_recorder(
        main::media_stream* stream_option,
        detail::media_recorder_options&& options)
{
    decltype(auto) mime_type_option = options.try_emplace("mimeType", "").first->second.to<decltype(mime_type)::value_t>();
    decltype(auto) bits_per_second_option = options.try_emplace("bitsPerSecond").first->second.to<decltype(s_constrained_bits_per_second)::value_t>();

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [mime_type = std::move(mime_type_option)] {return !media_recorder::is_type_supported(mime_type);},
            "'mimeType' option is not supported");

    s_constrained_mime_type = std::move(mime_type_option);
    s_constrained_bits_per_second = std::move(bits_per_second_option);

    stream = stream_option;
    mime_type = s_constrained_mime_type();
    state = detail::recording_state_t::INACTIVE;

    // TODO : check default (audio-default + video-default ~= constrained-default)
    video_bits_per_second = options.try_emplace("videoBitsPerSecond", 1024).first->second.to<decltype(video_bits_per_second)::value_t>();
    audio_bits_per_second = options.try_emplace("audioBitsPerSecond", 4096).first->second.to<decltype(audio_bits_per_second)::value_t>();
    audio_bitrate_mode = options.try_emplace("audioBitrateMode", detail::bitrate_mode_t::VARIABLE).first->second.to<decltype(audio_bitrate_mode)::value_t>();
}


auto mediacapture::record::media_recorder::start(
        ext::number<ulong> timeslice)
        -> void
{
    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [state = state()] {return state != detail::recording_state_t::INACTIVE;},
            "The 'state' property must not be \"inactive\"");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [stream = stream()] {return !stream->active();},
            "The 'stream' property must be \"active\"");

    decltype(auto) tracks = stream()->get_tracks() | ranges::views::filter(detail::is_live_track);
    // TODO: webrtc check
    // TODO: constrain mime-type
    // TODO: constrain bits
    // TODO: lots

    GO []
    {
        // TODO
    };
}
