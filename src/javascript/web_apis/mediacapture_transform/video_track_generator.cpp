#include "video_track_generator.hpp"
#include "video_track_generator_private.hpp"

#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_main/media_stream_track_private.hpp"
#include "streams/writable/writable_stream.hpp"


mediacapture::transform::video_track_generator::video_track_generator()
{
    INIT_PIMPL(video_track_generator);

    ACCESS_PIMPL(video_track_generator);
    d->writable = std::make_unique<streams::writable::writable_stream>();
    d->track = std::make_unique<main::media_stream_track>();
    d->track->d_func()->source = this;
    d->track->d_func()->tie_source_to_context = false;
}
