#include "track_internals.hpp"




#include "mediacapture_main/media_stream_track.hpp"


auto mediacapture::detail::track_ends_for_any_reason_except_stop(
        main::media_stream_track* track)
        -> void
{
    // queue steps to stop the track and fire an "ended" event at the track
    dom::detail::observer_internals::queue_microtask(
            [&track]
            {track->stop(); dom::detail::event_internals::fire_event("ended", track);});
}
