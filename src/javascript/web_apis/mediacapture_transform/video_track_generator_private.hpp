#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_PRIVATE_HPP

#include "ext/pimpl.ixx"



namespace mediacapture::main {class media_stream_track;}
namespace streams::writable {class writable_stream;}


DEFINE_PRIVATE_CLASS(mediacapture::transform, video_track_generator) : virtual dom_object_private
{
    std::unique_ptr<streams::writable::writable_stream> writable;
    std::unique_ptr<main::media_stream_track> track;
    ext::boolean is_muted;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_VIDEO_TRACK_GENERATOR_PRIVATE_HPP
