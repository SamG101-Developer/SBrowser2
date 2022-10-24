#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_STREAM_TRACK_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_STREAM_TRACK_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event_private.hpp"

#include "ext/memory.hpp"
namespace mediacapture::main {class media_stream_track;}


DEFINE_PRIVATE_CLASS(mediacapture::main, media_stream_track_event) : dom::events::event_private
{
    std::observer_ptr<media_stream_track> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_STREAM_TRACK_EVENT_PRIVATE_HPP
