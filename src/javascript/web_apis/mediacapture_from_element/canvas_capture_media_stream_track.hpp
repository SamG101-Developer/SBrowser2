#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPTURE_FROM_ELEMENT_CANVAS_CAPTURE_MEDIA_STREAM_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPTURE_FROM_ELEMENT_CANVAS_CAPTURE_MEDIA_STREAM_TRACK_HPP

#include "mediacapture_main/media_stream_track.hpp"
namespace mediacapture::from_element {class canvas_capture_media_stream_track;}
namespace mediacapture::from_element {class canvas_capture_media_stream_track_private;}

namespace html::elements {class html_canvas_element;}


class mediacapture::from_element::canvas_capture_media_stream_track
        : public main::media_stream_track
{
public constructors:
    canvas_capture_media_stream_track();
    MAKE_PIMPL(canvas_capture_media_stream_track);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto request_frame() -> void;

private js_properties:
    DEFINE_GETTER(canvas, html::elements::html_canvas_element*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPTURE_FROM_ELEMENT_CANVAS_CAPTURE_MEDIA_STREAM_TRACK_HPP
