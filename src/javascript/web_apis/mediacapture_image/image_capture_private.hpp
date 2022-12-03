#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE_IMAGE_CAPTURE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE_IMAGE_CAPTURE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/memory.ixx"
namespace mediacapture::main {class media_stream_track;}


DEFINE_PRIVATE_CLASS(mediacapture::image, image_capture) : virtual dom_object_private
{
    std::observer_ptr<main::media_stream_track> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE_IMAGE_CAPTURE_PRIVATE_HPP
