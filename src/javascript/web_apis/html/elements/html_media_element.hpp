#pragma once
#ifndef SBROWSER2_HTML_MEDIA_ELEMENT_HPP
#define SBROWSER2_HTML_MEDIA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_media_element;}

#include USE_INNER_TYPES(html)
namespace html::basic_media {class media_error;}
namespace html::basic_media {class time_ranges;}
namespace html::basic_media {class audio_track;}
namespace html::basic_media {class video_track;}
namespace html::basic_media {class text_track;}
namespace mediacapture::main {class media_stream;}


class html::elements::html_media_element
        : public html_element
{
public js_static_constants:
    constexpr static const ext::number<ushort> NETWORK_EMPTY = 0;
    constexpr static const ext::number<ushort> NETWORK_IDLE = 1;
    constexpr static const ext::number<ushort> NETWORK_LOADING = 2;
    constexpr static const ext::number<ushort> NETWORK_NO_SOURCE = 3;

    constexpr static const ext::number<ushort> HAVE_NOTHING = 0;
    constexpr static const ext::number<ushort> HAVE_METADATA = 1;
    constexpr static const ext::number<ushort> HAVE_CURRENT_DATA = 2;
    constexpr static const ext::number<ushort> HAVE_FUTURE_DATA = 3;
    constexpr static const ext::number<ushort> HAVE_ENOUGH_DATA = 4;

public js_methods:
    /* HTML */
    auto load() -> void;
    auto can_play_type(ext::string_view type) -> detail::can_play_type_result_t;
    auto fast_seek(const ext::number<double>& time) -> void;
    auto get_start_date() -> ext::any;
    auto play() -> ext::promise<void>;
    auto pause() -> void;
    auto add_text_track(detail::text_track_kind_t kind, ext::string&& label = "", ext::string laguage = "") -> basic_media::text_track;

    /* MEDIACAPTURE-FROMELEMENT */
    auto capture_stream() -> mediacapture::main::media_stream;

    /* MEDIACAPTURE_OUTPUT */
    auto set_sink_id(ext::string&& sink_id) -> ext::promise<void>;

public cpp_properties:
    ext::property<basic_media::media_error*> error;

    ext::property<ext::string> cross_origin;
    ext::property<ext::string> preload;
    ext::property<ext::string> src;
    ext::property<detail::media_provider_t> src_object;
    ext::property<ext::number<ushort>> network_state;
    ext::property<basic_media::time_ranges*> buffered;

    ext::property<ext::number<ushort>> ready_state;
    ext::property<ext::boolean> seeking;

    ext::property<ext::number<double>> current_time;
    ext::property<ext::number<double>> duration;
    ext::property<ext::number<double>> default_playback_rate;
    ext::property<ext::number<double>> playback_rate;
    ext::property<basic_media::time_ranges*> played;
    ext::property<basic_media::time_ranges*> seekable;
    ext::property<ext::boolean> preserves_pitch;
    ext::property<ext::boolean> paused;
    ext::property<ext::boolean> ended;
    ext::property<ext::boolean> autoplay;
    ext::property<ext::boolean> loop;

    ext::property<ext::number<double>> volume;
    ext::property<ext::boolean> controls;
    ext::property<ext::boolean> muted;
    ext::property<ext::boolean> default_muted;

    ext::property<std::unique_ptr<ext::vector<basic_media::audio_track*>>> audio_tracks;
    ext::property<std::unique_ptr<ext::vector<basic_media::video_track*>>> video_tracks;
    ext::property<std::unique_ptr<ext::vector<basic_media::text_track*>>> text_tracks;

    /* MEDIACAPTURE_OUTPUT */
    ext::property<ext::string> sink_id;
};


#endif //SBROWSER2_HTML_MEDIA_ELEMENT_HPP
