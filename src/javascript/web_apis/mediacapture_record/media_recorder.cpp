#include "media_recorder.hpp"
#include "media_recorder_private.hpp"



#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "mediacapture_main/detail/track_internals.hpp"
#include "mediacapture_main/media_stream.hpp"
#include "mediacapture_main/media_stream_private.hpp"
#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_main/media_stream_track_private.hpp"
#include "mediacapture_record/_typedefs.hpp"


mediacapture::record::media_recorder::media_recorder(
        main::media_stream* stream,
        detail::media_recorder_options&& options)
{
    INIT_PIMPL(media_recorder);
    using enum dom::detail::dom_exception_error_t;

    ACCESS_PIMPL(media_recorder);
    decltype(auto) mime_type_option = options[u"mimeType"].to<decltype(d->mime_type)>();
    decltype(auto) bits_per_second_option = options["bitsPerSecond"].to<decltype(d->constrained_bits_per_second)>();

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [mime_type = std::move(mime_type_option)] {return !media_recorder::is_type_supported(mime_type);},
            u8"'mimeType' option is not supported");

    d->constrained_mime_type = std::move(mime_type_option);
    d->constrained_bits_per_second = std::move(bits_per_second_option);

    d->stream = stream;
    d->mime_type = d->constrained_mime_type;
    d->state = detail::recording_state_t::INACTIVE;

    d->video_bits_per_second = options[u"videoBitsPerSecond", 1024].to<decltype(d->video_bits_per_second)>();
    d->audio_bits_per_second = options[u"audioBitsPerSecond", 1024].to<decltype(d->audio_bits_per_second)>();
    d->audio_bitrate_mode = options[u"audioBitrateMode", detail::bitrate_mode_t::VARIABLE].to<decltype(d->audio_bitrate_mode)>();

    // TODO
}


auto mediacapture::record::media_recorder::start(
        ext::number<ulong> timeslice)
        -> void
{
    ACCESS_PIMPL(const media_recorder);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->state != detail::recording_state_t::INACTIVE;},
            u8"The 'state' property must not be \"inactive\"");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return !d->stream->active();},
            u8"The 'stream' property must be \"active\"");

    decltype(auto) tracks = d->stream->get_tracks() | ranges::views::filter(detail::is_live_track);
    // TODO
}


auto mediacapture::record::media_recorder::get_stream() const -> main::media_stream*
{
    ACCESS_PIMPL(const media_recorder);
    return d->stream.get();
}


auto mediacapture::record::media_recorder::get_mime_type() const -> ext::string_view
{
    ACCESS_PIMPL(const media_recorder);
    return d->mime_type;
}


auto mediacapture::record::media_recorder::get_state() const -> detail::recording_state_t
{
    ACCESS_PIMPL(const media_recorder);
    return d->state;
}


auto mediacapture::record::media_recorder::get_video_bits_per_second() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const media_recorder);
    return d->video_bits_per_second;
}


auto mediacapture::record::media_recorder::get_audio_bits_per_second() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const media_recorder);
    return d->audio_bits_per_second;
}


auto mediacapture::record::media_recorder::get_audio_bitrate_mode() const -> detail::bitrate_mode_t
{
    ACCESS_PIMPL(const media_recorder);
    return d->audio_bitrate_mode;
}
