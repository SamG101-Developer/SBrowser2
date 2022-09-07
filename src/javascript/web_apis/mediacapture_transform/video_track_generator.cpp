#include "video_track_generator.hpp"

#include "mediacapture_main/media_stream_track.hpp"


mediacapture::transform::video_track_generator::video_track_generator()
        : track{std::make_unique<main::media_stream_track>()}
        , writeable{std::make_unique<streams::writable::writable_stream>()}
{
    streams::detail::setup_writable(writeable(), )
}
