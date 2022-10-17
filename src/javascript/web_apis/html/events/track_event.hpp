#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_HPP

#include "dom/events/event.hpp"
namespace html::events {class track_event;}
namespace html::events {class track_event_private;}

namespace html::basic_media {class abstract_track;}


class html::events::track_event
        : public dom::events::event
{
public constructors:
    track_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(track_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(track, basic_media::abstract_track*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_HPP
