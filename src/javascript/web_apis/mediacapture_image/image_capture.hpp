#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE_IMAGE_CAPTURE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE_IMAGE_CAPTURE_HPP

#include "dom_object.hpp"
namespace mediacapture::image {class image_capture;}

#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(mediacapture_image)
namespace file_api {class blob;}
namespace mediacapture::main {class media_stream_track;}


class mediacapture::image::image_capture
        : public dom_object
{
public constructors:
    image_capture() = default;
    image_capture(main::media_stream_track* video_track);

public js_methods:
    auto take_photo(detail::photo_settings_t&& photo_settings = {}) -> ext::promise<file_api::blob*>;
    auto get_photo_capabilties() -> ext::promise<detail::photo_capabilities_t>;
    auto get_photo_settings() -> ext::promise<detail::photo_settings_t>;
    auto grab_frame() -> ext::promise<html::canvasing::image_bitmap*>;

private js_properties:
    ext::property<std::unique_ptr<main::media_stream_track>> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_IMAGE_IMAGE_CAPTURE_HPP
