#include "track_internals.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "mediacapture_main/media_stream_track.hpp"


auto mediacapture::detail::track_internals::track_ends_for_any_reason_except_stop(
        main::media_stream_track* track)
        -> void
{
    auto task = [track]
    {
        // if the track has already ended, then this method will do nothing, so return early at the return-guard, otherwise
        // set the ready state to ended, so that the track knows it has ended, and progress with the rest of the method
        return_if(track->ready_state() == "ended");
        track->ready_state = "ended";

        // notify the source that the track has ended so that the source can be stopped, and then fire an "ended" event at
        // the 'track', so that any listeners that want to know when a track has ended can be executed
        // TODO : notify source that the track has ended
        dom::detail::event_internals::fire_event("ended", track);
    };

    // queue the above steps onto the dom manipulation task source TODO : is this the correct task source, and queue
    //  method?
    dom::detail::observer_internals::queue_task(
            html::detail::task_internals::dom_manipulation_task_source(),
            task);
}
