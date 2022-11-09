#include "media_stream_track.hpp"
#include "media_stream_track_private.hpp"

#include "ext/uuid.hpp"

#include "dom/detail/event_internals.hpp"
#include "mediacapture_main/detail/source_internals.hpp"
#include "uuid.h"


mediacapture::main::media_stream_track::media_stream_track(
        detail::media_stream_track_source_t& source,
        ext::boolean tie_source_to_context) // TODO : params?
{
    INIT_PIMPL(media_stream_track);

    ACCESS_PIMPL(media_stream_track);
    d->id = ext::to_string(ext::uuid_system_generator{}());
    d->kind = source.source_type;
    d->ready_state = detail::media_stream_track_state_t::LIVE;
    d->enabled = true;
    d->muted = source.muted;

    if (tie_source_to_context) detail::tie_track_source_to_context(source);
    source.source_specific_construction_steps(this);
}


auto mediacapture::main::media_stream_track::clone()
        const -> media_stream_track
{
    ACCESS_PIMPL(const media_stream_track);

    // create a new MediaStreamTrack object that has the same source as this track, and clone the '[[capabilities]],
    // [[constraints]], and the [[settings]], by using the copy constructor of the `ext::map<ext::string, ext::any>`
    // objects
    auto track_clone = media_stream_track{*d->source, false};
    track_clone.d_func()->capabilities = auto{d->capabilities};
    track_clone.d_func()->constraints = auto{d->constraints};
    track_clone.d_func()->settings = auto{d->settings};

    // run the coning steps on the track, wit the current track and newly cloned track as the two parameters, and then
    // return the newly cloned track
    d->source->source_specific_cloning_steps(this, &track_clone);
    return track_clone;
}


auto mediacapture::main::media_stream_track::stop() -> void
{
    ACCESS_PIMPL(media_stream_track);

    // if the track has already ended, then this method will do nothing, so return early at the return-guard, otherwise
    // set the ready state to ended, so that the track knows it has ended, and progress with the rest of the method
    return_if(d->ready_state == detail::media_stream_track_state_t::ENDED);
    d->ready_state = detail::media_stream_track_state_t::ENDED;

    // notify the source that the track has ended so that the source can be stopped, and then fire an "ended" event at
    // the 'track', so that any listeners that want to know when a track has ended can be executed
    // TODO : notify source that the track has ended
}


auto mediacapture::main::media_stream_track::get_kind() const -> ext::string_view
{
    ACCESS_PIMPL(const media_stream_track);
    return d->kind;
}


auto mediacapture::main::media_stream_track::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const media_stream_track);
    return d->id;
}


auto mediacapture::main::media_stream_track::get_label() const -> ext::string_view
{
    ACCESS_PIMPL(const media_stream_track);
    return d->label;
}


auto mediacapture::main::media_stream_track::get_enabled() const -> ext::boolean
{
    ACCESS_PIMPL(const media_stream_track);
    return d->enabled;
}


auto mediacapture::main::media_stream_track::get_muted() const -> ext::boolean
{
    ACCESS_PIMPL(const media_stream_track);
    return d->muted;
}


auto mediacapture::main::media_stream_track::get_ready_state() const -> detail::media_stream_track_state_t
{
    ACCESS_PIMPL(const media_stream_track);
    return d->ready_state;
}


auto mediacapture::main::media_stream_track::set_enabled(ext::boolean new_enabled) -> ext::boolean
{
    ACCESS_PIMPL(media_stream_track);
    return d->enabled = new_enabled;
}
