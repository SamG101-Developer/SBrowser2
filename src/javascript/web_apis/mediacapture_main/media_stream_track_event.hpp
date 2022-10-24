#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_TRACK_EVENT_HPP
#define SBROWSER2_MEDIA_STREAM_TRACK_EVENT_HPP

#include "dom/events/event.hpp"
namespace mediacapture::main {class media_stream_track_event;}
namespace mediacapture::main {class media_stream_track_event_private;}

#include "ext/property.hpp"
namespace mediacapture::main {class media_stream_track;}


class mediacapture::main::media_stream_track_event
        : public dom::events::event
{
public constructors:
    media_stream_track_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(media_stream_track_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(track, media_stream_track*);
};


#endif //SBROWSER2_MEDIA_STREAM_TRACK_EVENT_HPP
