#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_TRACK_EVENT_HPP
#define SBROWSER2_MEDIA_STREAM_TRACK_EVENT_HPP

#include "dom/events/event.hpp"
namespace mediacapture::main {class media_stream_track_event;}

#include "ext/property.hpp"
namespace mediacapture::main {class media_stream_track;}


class mediacapture::main::media_stream_track_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(media_stream_track_event);
    media_stream_track_event() = default;
    media_stream_track_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<media_stream_track*> track;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_MEDIA_STREAM_TRACK_EVENT_HPP
