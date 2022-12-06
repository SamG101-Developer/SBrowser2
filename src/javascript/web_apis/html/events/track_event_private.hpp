#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"


namespace html::basic_media {class abstract_track;}


DEFINE_PRIVATE_CLASS(html::events, track_event) : dom::events::event_private
{
    std::unique_ptr<basic_media::abstract_track> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_EVENTS_TRACK_EVENT_PRIVATE_HPP
