#pragma once
#ifndef SBROWSER2_HTML_MEDIA_ELEMENT_HPP
#define SBROWSER2_HTML_MEDIA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_media_element;}
namespace html::elements {class html_media_element_private;}

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include "ext/ranges.hpp"
namespace html::basic_media {class media_error;}
namespace html::basic_media {class time_ranges;}
namespace html::basic_media {class audio_track;}
namespace html::basic_media {class video_track;}
namespace html::basic_media {class text_track;}
namespace html::basic_media {class text_track_cue;}
namespace html::messaging {class message_channel;}
namespace html::messaging {class message_port;}
namespace mediacapture::main {class media_stream;}


class html::elements::html_media_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_media_element);
    MAKE_PIMPL(html_media_element);
    MAKE_V8_AVAILABLE;
    ~html_media_element();

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
    /* [HTML] */
    auto load() -> void;
    auto can_play_type(ext::string_view type) -> detail::can_play_type_result_t;
    auto fast_seek(ext::number<double> time) -> void;
    auto get_start_date() -> ext::any;
    auto play() -> ext::promise<void>;
    auto pause() -> void;
    auto add_text_track(detail::text_track_kind_t kind, ext::string&& label = u8"", ext::string laguage = u8"") -> basic_media::text_track;

    /* [MEDIACAPTURE-FROMELEMENT] */
    auto capture_stream() -> mediacapture::main::media_stream;

    /* [MEDIACAPTURE-OUTPUT] */
    auto set_sink_id(ext::string&& sink_id) -> ext::promise<void>;

private js_properties:
    // Error State
    DEFINE_GETTER(error, basic_media::media_error*);

    // Network State
    DEFINE_GETTER(src, ext::string_view);
    DEFINE_GETTER(src_object, detail::media_provider_t);
    DEFINE_GETTER(current_src, ext::string_view);
    DEFINE_GETTER(cross_origin, detail::cross_origin_settings_attribute_t);
    DEFINE_GETTER(network_state, ext::number<ushort>);
    DEFINE_GETTER(preload, detail::preload_t);
    DEFINE_GETTER(buffered, basic_media::time_ranges*); // TODO : Impl?

    // Ready State
    DEFINE_GETTER(ready_state, ext::number<ushort>);
    DEFINE_GETTER(seeking, ext::boolean);

    // Playback State
    DEFINE_GETTER(current_time, ext::number<double>);
    DEFINE_GETTER(duration, ext::number<double>);
    DEFINE_GETTER(paused, ext::boolean);
    DEFINE_GETTER(default_playback_rate, ext::number<double>);
    DEFINE_GETTER(playback_rate, ext::number<double>);
    DEFINE_GETTER(preserves_pitch, ext::boolean);
    DEFINE_GETTER(played, basic_media::time_ranges*);
    DEFINE_GETTER(seekable, basic_media::time_ranges*);
    DEFINE_GETTER(ended, ext::boolean);
    DEFINE_GETTER(autoplay, ext::boolean);
    DEFINE_GETTER(loop, ext::boolean);

    // Controls
    DEFINE_GETTER(controls, ext::boolean);
    DEFINE_GETTER(volume, ext::number<double>);
    DEFINE_GETTER(muted, ext::boolean);
    DEFINE_GETTER(default_muted, ext::boolean);

    // Tracks
    DEFINE_GETTER(audio_tracks, ext::vector_span<basic_media::audio_track*>);
    DEFINE_GETTER(video_tracks, ext::vector_span<basic_media::video_track*>);
    DEFINE_GETTER(text_tracks, ext::vector_span<basic_media::text_track*>);


    DEFINE_SETTER(src, ext::string);
    DEFINE_SETTER(src_object, detail::media_provider_t);
    DEFINE_SETTER(cross_origin, fetch::detail::mode_t);
    DEFINE_SETTER(preload, detail::preload_t);

    DEFINE_SETTER(current_time, ext::number<double>);
    DEFINE_SETTER(default_playback_rate, ext::number<double>);
    DEFINE_SETTER(playback_rate, ext::number<double>);
    DEFINE_SETTER(preserves_pitch, ext::boolean);
    DEFINE_SETTER(autoplay, ext::boolean);
    DEFINE_SETTER(loop, ext::boolean);

    DEFINE_SETTER(controls, ext::boolean);
    DEFINE_SETTER(volume, ext::number<double>);
    DEFINE_SETTER(muted, ext::boolean);
    DEFINE_SETTER(default_muted, ext::boolean);

    /* [MEDIACAPTURE-OUTPUT] */
    DEFINE_GETTER(sink_id, ext::string);
};


#endif //SBROWSER2_HTML_MEDIA_ELEMENT_HPP
