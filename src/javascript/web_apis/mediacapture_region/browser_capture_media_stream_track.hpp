#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_BROWSER_CAPTURE_MEDIA_STREAM_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_BROWSER_CAPTURE_MEDIA_STREAM_TRACK_HPP

#include "mediacapture_main/media_stream_track.hpp"
namespace mediacapture::region {class browser_capture_media_stream_track;}

namespace mediacapture::region {class crop_target;}


class mediacapture::region::browser_capture_media_stream_track
        : public main::media_stream_track
{
public constructors:
    DOM_CTORS(browser_capture_media_stream_track);
    browser_capture_media_stream_track() = default;

public js_methods:
    auto crop_to(crop_target* crop_target) -> ext::promise<void>;
    auto clone() -> browser_capture_media_stream_track;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const&& -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_BROWSER_CAPTURE_MEDIA_STREAM_TRACK_HPP
