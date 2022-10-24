#include "canvas_capture_media_stream_track.hpp"
#include "canvas_capture_media_stream_track_private.hpp"


auto mediacapture::from_element::canvas_capture_media_stream_track::get_canvas() const -> html::elements::html_canvas_element*
{
    ACCESS_PIMPL(const canvas_capture_media_stream_track);
    return d->canvas.get();
}
