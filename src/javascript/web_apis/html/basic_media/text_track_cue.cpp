#include "text_track_cue.hpp"
#include "text_track_cue_private.hpp"




auto html::basic_media::text_track_cue::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const text_track_cue);
    return d->id;
}


auto html::basic_media::text_track_cue::get_start_time() const -> ext::number<double>
{
    ACCESS_PIMPL(const text_track_cue);
    return d->start_time;
}


auto html::basic_media::text_track_cue::get_end_time() const -> ext::number<double>
{
    ACCESS_PIMPL(const text_track_cue);
    return d->end_time;
}


auto html::basic_media::text_track_cue::get_pause_on_exit() const -> ext::boolean
{
    ACCESS_PIMPL(const text_track_cue);
    return d->pause_on_exit_flag;
}


auto html::basic_media::text_track_cue::set_id(ext::string new_id) -> ext::string
{
    ACCESS_PIMPL(text_track_cue);
    return d->id = new_id;
}


auto html::basic_media::text_track_cue::set_start_time(ext::number<double> new_start_time) -> ext::number<double>
{
    ACCESS_PIMPL(text_track_cue);
    return d->start_time = new_start_time;
}


auto html::basic_media::text_track_cue::set_end_time(ext::number<double> new_end_time) -> ext::number<double>
{
    ACCESS_PIMPL(text_track_cue);
    return d->end_time = new_end_time;
}


auto html::basic_media::text_track_cue::set_pause_on_exit(ext::boolean new_pause_on_exit) -> ext::boolean
{
    ACCESS_PIMPL(text_track_cue);
    return d->pause_on_exit_flag = new_pause_on_exit;
}


auto html::basic_media::text_track_cue::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<text_track_cue>{isolate}
        .inherit<dom::nodes::event_target>()
        .property("id", &text_track_cue::get_id)
        .property("startTime", &text_track_cue::get_start_time)
        .property("endTime", &text_track_cue::get_end_time)
        .property("pauseOnExit", &text_track_cue::get_pause_on_exit)
        .property("track", &text_track_cue::get_track)
        .auto_wrap_objects();

    return std::move(conversion);
}
