#include "media_stream_track_event.hpp"
#include "media_stream_track_event_private.hpp"

#include "mediacapture_main/media_stream_track.hpp"


mediacapture::main::media_stream_track_event::media_stream_track_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(media_stream_track_event);

    ACCESS_PIMPL(media_stream_track_event);
    d->track = event_init[u"track"].to<decltype(d->track)::pointer>();
}


auto mediacapture::main::media_stream_track_event::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<media_stream_track_event>{isolate}
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .property("track", &media_stream_track_event::get_track)
        .auto_wrap_objects();

    return std::move(conversion);
}
