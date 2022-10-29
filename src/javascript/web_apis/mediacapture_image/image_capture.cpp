#include "image_capture.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"
#include "mediacapture_main/media_stream_track.hpp"


mediacapture::image::image_capture::image_capture(
        main::media_stream_track* video_track)
        : track{std::unique_ptr<main::media_stream_track>(video_track)}
{
    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [track = track()] {return track->kind() != "video";},
            "The 'track' property must have a 'kind' attribute set to \"video\"");
}
