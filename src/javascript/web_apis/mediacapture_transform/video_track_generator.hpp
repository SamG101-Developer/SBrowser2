#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_HPP

#include "dom_object.hpp"
namespace mediacapture::transform {class video_track_generator;}

#include "ext/boolean.hpp"
namespace streams::writable {class writable_stream;}
namespace mediacapture::main {class media_stream_track;}


class mediacapture::transform::video_track_generator
        : public virtual dom_object
{
public constructors:
    video_track_generator() = default;

private js_properties:
    ext::property<std::unique_ptr<streams::writable::writable_stream>> writable;
    ext::property<std::unique_ptr<main::media_stream_track>> track;
    ext::property<ext::boolean> muted;

private js_slots:
    ext::slot<std::unique_ptr<main::media_stream_track>> s_track;
    ext::property<ext::boolean> s_muted;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_HPP
