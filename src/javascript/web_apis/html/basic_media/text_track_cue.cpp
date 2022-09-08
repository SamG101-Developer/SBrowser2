#include "text_track_cue.hpp"

#include "dom/nodes/event_target.hpp"

#include <v8pp/class.hpp>


auto html::basic_media::text_track_cue::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<text_track_cue>{isolate}
        .inherit<dom::nodes::event_target>()
        .var("id", &text_track_cue::id, false)
        .var("startTime", &text_track_cue::start_time, false)
        .var("endTime", &text_track_cue::end_time, false)
        .var("pauseOnExit", &text_track_cue::pause_on_exit, false)
        .var("track", &text_track_cue::track, true)
        .auto_wrap_objects();
}
