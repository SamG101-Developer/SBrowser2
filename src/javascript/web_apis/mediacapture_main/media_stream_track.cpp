#include "media_stream_track.hpp"

#include "ext/uuid.hpp"

#include "dom/detail/event_internals.hpp"
#include "mediacapture_main/details/source_internals.hpp"


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
        , m_source{source}
{
    if (tie_source_to_context) detail::source_internals::tie_track_source_to_context(source);
    source.source_specific_construction_steps(this);
}


auto mediacapture::main::media_stream_track::clone()
        const -> media_stream_track
{
    // create a new MediaStreamTrack object that has the same source as this track, and clone the '[[capabilities]],
    // [[constraints]], and the [[settings]], by using the copy constructor of the `ext::map<ext::string, ext::any>`
    // objects
    media_stream_track track_clone{m_source, ext::boolean::FALSE_()};
    track_clone.s_capabilities = ext::map<ext::string, ext::any>{s_capabilities};
    track_clone.s_constraints = ext::map<ext::string, ext::any>{s_constraints};
    track_clone.s_settings = ext::map<ext::string, ext::any>{s_settings};

    // run the coning steps on the track, wit the current track and newly cloned track as the two parameters, and then
    // return the newly cloned track
    m_source.source_specific_cloning_steps(this, &track_clone);
    return track_clone;
}


auto mediacapture::main::media_stream_track::set_muted(
        ext::boolean_view val)
        -> void
{
    // don't do anything if the 'new_state' is the same as the current state, because otherwise multiple "mute" /
    // "unmute" event would be received when there is no change to the data
    return_if(muted() == val);
    property_guard(muted);
    *muted = val;

    // fire an event that is either "mute" or "unmute" depending on the 'new_state', at this track
    dom::detail::event_internals::fire_event(val ? "mute" : "unmute", this);
}