#include "media_stream_track.hpp"

#include "ext/uuid.hpp"

#include "dom/detail/event_internals.hpp"
#include "mediacapture_main/detail/source_internals.hpp"


mediacapture::main::media_stream_track::media_stream_track(
        detail::media_stream_track_source& source,
        ext::boolean tie_source_to_context)

        : id{ext::to_string(ext::uuid_system_generator{}())}
        , kind{std::is_same_v<decltype(source)::source_type, audio_stream_track> ? "audio" : "video"}
        , label{source.label}
        , ready_state{"live"}
        , enabled{true}
        , muted{source.muted}
        , m_source{source}
{
    if (tie_source_to_context) detail::tie_track_source_to_context(source);
    source.source_specific_construction_steps(this);
}


auto mediacapture::main::media_stream_track::clone()
        const -> media_stream_track
{
    // create a new MediaStreamTrack object that has the same source as this track, and clone the '[[capabilities]],
    // [[constraints]], and the [[settings]], by using the copy constructor of the `ext::map<ext::string, ext::any>`
    // objects
    media_stream_track track_clone{m_source, ext::boolean::FALSE_()};
    track_clone.s_capabilities = auto{s_capabilities};
    track_clone.s_constraints = auto{s_constraints};
    track_clone.s_settings = auto{s_settings};

    // run the coning steps on the track, wit the current track and newly cloned track as the two parameters, and then
    // return the newly cloned track
    m_source.source_specific_cloning_steps(this, &track_clone);
    return track_clone;
}


auto mediacapture::main::media_stream_track::stop() -> void
{
    // if the track has already ended, then this method will do nothing, so return early at the return-guard, otherwise
    // set the ready state to ended, so that the track knows it has ended, and progress with the rest of the method
    return_if(ready_state() == "ended");
    ready_state = "ended";

    // notify the source that the track has ended so that the source can be stopped, and then fire an "ended" event at
    // the 'track', so that any listeners that want to know when a track has ended can be executed
    // TODO : notify source that the track has ended
}


auto mediacapture::main::media_stream_track::set_muted(
        ext::boolean  val)
        -> void
{
    // don't do anything if the 'new_state' is the same as the current state, because otherwise multiple "mute" /
    // "unmute" event would be received when there is no change to the data
    return_if(muted() == val);
    guard_property(muted);
    *muted = val;

    // fire an event that is either "mute" or "unmute" depending on the 'new_state', at this track
    dom::detail::fire_event(val ? "mute" : "unmute", this);
}