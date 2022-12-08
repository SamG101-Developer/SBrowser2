#include "image_capture.hpp"
#include "image_capture_private.hpp"




#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_main/media_stream_track_private.hpp"


mediacapture::image::image_capture::image_capture(
        main::media_stream_track* video_track)
{
    INIT_PIMPL(image_capture);
    using enum dom::detail::dom_exception_error_t;

    ACCESS_PIMPL(image_capture);
    d->track = video_track;

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->track->d_func()->kind != u"video";},
            u8"The 'track' property must have a 'kind' attribute set to \"video\"");
}
