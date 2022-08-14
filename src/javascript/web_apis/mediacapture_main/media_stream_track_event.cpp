#include "media_stream_track_event.hpp"

#include "mediacapture_main/media_stream_track.hpp"


mediacapture::main::media_stream_track_event::media_stream_track_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS(event_init, track, nullptr)
{}


auto mediacapture::main::media_stream_track_event::to_v8(
        v8::Isolate* isolate) const &&
        -> ext::any
{
    return v8pp::class_<media_stream_track_event>{isolate}
            .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
            .var("track", &media_stream_track_event::track, true)
            .auto_wrap_objects();
}
