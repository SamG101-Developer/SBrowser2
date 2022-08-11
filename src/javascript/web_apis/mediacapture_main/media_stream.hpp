#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_HPP
#define SBROWSER2_MEDIA_STREAM_HPP

#include "dom/nodes/event_target.hpp"
namespace mediacapture::main {class media_stream;}

#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace mediacapture::main {class media_stream_track;}


class mediacapture::main::media_stream
        : public dom::nodes::event_target
{
public constructors:
    media_stream();
    explicit media_stream(media_stream* stream);
    explicit media_stream(ext::vector<media_stream_track*>&& tracks);

public js_properties:
    ext::property<ext::boolean> active;
    ext::property<ext::string> id;

public js_methods:
    _EXT_NODISCARD auto get_tracks() const -> ranges::any_view<media_stream_track*, ranges::category::forward>;
    _EXT_NODISCARD auto get_audio_tracks() const -> ranges::any_view<media_stream_track*, ranges::category::forward>;
    _EXT_NODISCARD auto get_video_tracks() const -> ranges::any_view<media_stream_track*, ranges::category::forward>;

    _EXT_NODISCARD auto get_track_by_id(ext::string_view track_id) const -> media_stream_track*;
    auto add_track(media_stream_track* track) -> void;
    auto remove_track(media_stream_track* track) -> void;
    _EXT_NODISCARD auto clone() const -> media_stream;

private cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::set<media_stream_track*> m_track_set;
};


#endif //SBROWSER2_MEDIA_STREAM_HPP
