#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_HPP

#include "dom/events/event.hpp"
namespace html::events {class track_event;}

namespace html::basic_media {class abstract_track;}


class html::events::track_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(track_event);
    track_event() = default;
    track_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<basic_media::abstract_track*> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_HPP
