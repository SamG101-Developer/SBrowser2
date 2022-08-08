#include "media_stream_track.hpp"

#include "mediacapture_main/details/source_internals.hpp"

#include "ext/uuid.hpp"


template <inherit<mediacapture::main::media_stream_track> T>
mediacapture::main::media_stream_track::media_stream_track(
        detail::source_internals::media_stream_track_source<T>& source,
        ext::boolean_view tie_source_to_context)

        : id{ext::to_string(ext::uuid_system_generator{}())}
        , kind{std::is_same_v<decltype(source)::source_type, audio_stream_track> ? "audio" : "video"}
        , label{source.label}
        , ready_state{"live"}
        , enabled{ext::boolean::TRUE_()}
        , muted{source.muted}
{
    if (tie_source_to_context) detail::source_internals::tie_track_source_to_context(source);
    source.source_specific_construction_steps(this);
}