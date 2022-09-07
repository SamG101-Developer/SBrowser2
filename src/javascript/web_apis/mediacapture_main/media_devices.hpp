#pragma once
#ifndef SBROWSER2_MEDIA_DEVICES_HPP
#define SBROWSER2_MEDIA_DEVICES_HPP

#include "dom/nodes/event_target.hpp"
namespace mediacapture::main {class media_devices;}

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "ext/promise.hpp"
#include USE_INNER_TYPES(mediacapture_extensions)
#include USE_INNER_TYPES(mediacapture_handle)
#include USE_INNER_TYPES(mediacapture_main)
#include USE_INNER_TYPES(mediacapture_output)
#include USE_INNER_TYPES(mediacapture_screenshare)
#include USE_INNER_TYPES(mediacapture_viewport)
namespace mediacapture::main {class media_device_info;}
namespace mediacapture::main {class media_stream;}


class mediacapture::main::media_devices
        : public dom::nodes::event_target
{
public js_properties:
    /* MEDIACAPTURE_EXTENSIONS */
    detail::get_user_media_semantics_t default_semantics;

public js_methods:
    auto enumerate_devices() -> ext::promise<ext::vector<media_device_info*>>;
    auto get_user_media(detail::constraints_t&& constraints = {}) -> ext::promise<media_stream*>;
    auto get_supported_constraints() -> detail::constraints_t;

    /* MEDIACAPTURE_OUTPUT */
    auto select_audio_output(detail::audio_output_options_t&& options = {}) -> ext::promise<media_device_info>;

    /* MEDIACAPTURE_HANDLE */
    auto set_capture_handle_config(detail::capture_handle_config_t&& config = {}) -> void;
    auto set_supported_capture_actions(ext::vector_view<ext::string> actions) -> void;

    /* MEDIACAPTURE_SCREENSHARE */
    auto get_display_media(detail::display_media_stream_options_t&& options = {}) -> ext::promise<media_stream*>;

    /* MEDIACAPTURE_VIEWPORT */
    auto get_viewport_media(detail::display_media_stream_constraints_t&& options = {}) -> ext::promise<media_stream*>;
};


#endif //SBROWSER2_MEDIA_DEVICES_HPP
