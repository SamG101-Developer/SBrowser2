#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_HPP

#include "dom_object.hpp"
namespace mediacapture::transform {class video_track_generator;}
namespace mediacapture::transform {class video_track_generator_private;}

#include "ext/boolean.hpp"
namespace streams::writable {class writable_stream;}
namespace mediacapture::main {class media_stream_track;}


class mediacapture::transform::video_track_generator
        : public virtual dom_object
{
public constructors:
    video_track_generator();
    MAKE_PIMPL(video_track_generator);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(writable, streams::writable::writable_stream*);
    DEFINE_GETTER(track, main::media_stream_track*);
    DEFINE_GETTER(muted, ext::boolean);

    DEFINE_SETTER(muted, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_HPP
