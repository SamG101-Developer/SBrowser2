#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_FROM_ELEMENT_CANVAS_CAPTURE_MEDIA_STREAM_TRACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_FROM_ELEMENT_CANVAS_CAPTURE_MEDIA_STREAM_TRACK_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "mediacapture_main/media_stream_track_private.hpp"

#include "ext/memory.ixx"


DEFINE_PRIVATE_CLASS(mediacapture::from_element, canvas_capture_media_stream_track) : mediacapture::media_stream_track_private
{
    std::observer_ptr<html::elements::html_canvas_element>
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_FROM_ELEMENT_CANVAS_CAPTURE_MEDIA_STREAM_TRACK_PRIVATE_HPP
