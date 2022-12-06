#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_HPP
#define SBROWSER2_MEDIA_STREAM_HPP


namespace mediacapture::main {class media_stream;}
namespace mediacapture::main {class media_stream_private;}

#include "ext/set.hpp"
#include "ext/vector.hpp"

namespace mediacapture::main {class media_stream_track;}


class mediacapture::main::media_stream
        : public dom::nodes::event_target
{
public constructors:
    media_stream();
    explicit media_stream(media_stream* stream);
    explicit media_stream(ext::vector<media_stream_track*>&& tracks);
    MAKE_PIMPL(media_stream);
    MAKE_V8_AVAILABLE;

public js_methods:
    _EXT_NODISCARD auto get_tracks() const -> ranges::any_view<media_stream_track*, ranges::category::forward>;
    _EXT_NODISCARD auto get_audio_tracks() const -> ranges::any_view<media_stream_track*, ranges::category::forward>;
    _EXT_NODISCARD auto get_video_tracks() const -> ranges::any_view<media_stream_track*, ranges::category::forward>;

    _EXT_NODISCARD auto get_track_by_id(ext::string_view track_id) const -> media_stream_track*;
    auto add_track(media_stream_track* track) -> void;
    auto remove_track(media_stream_track* track) -> void;
    _EXT_NODISCARD auto clone() const -> media_stream;

private js_properties:
    DEFINE_GETTER(active, ext::boolean);
    DEFINE_GETTER(id, ext::string_view);
};


#endif //SBROWSER2_MEDIA_STREAM_HPP
