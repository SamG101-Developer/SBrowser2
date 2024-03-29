#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_TRACK_HPP
#define SBROWSER2_MEDIA_STREAM_TRACK_HPP


#include "mediacapture_main/mixins/constrainable.hpp"
namespace mediacapture::main {class media_stream_track;}
namespace mediacapture::main {class media_stream_track_private;}

#include INCLUDE_INNER_TYPES(mediacapture_handle)
#include INCLUDE_INNER_TYPES(mediacapture_main)

#include "ext/span.hpp"


class mediacapture::main::media_stream_track
        : public dom::nodes::event_target
        , public mixins::constrainable // TODO : transfer steps defined in mediacapture-extensions API
{
public constructors:
    media_stream_track();
    MAKE_PIMPL(media_stream_track);
    MAKE_TRANSFERABLE(media_stream_track);
    MAKE_V8_AVAILABLE;

private constructors:
    media_stream_track(detail::media_stream_track_source_t& source, ext::boolean tie_source_to_context = true);

private js_methods:
    auto clone() const -> media_stream_track;
    auto stop() -> void;

    /* ↓ [MEDIACAPTURE-HANDLE] ↓ */
    auto get_capture_handle() -> detail::capture_handle_t;
    auto get_supported_capture_actions() -> ext::vector_span<ext::string>;
    auto send_capture_action(detail::capture_action_t action) -> ext::promise<void>;
    /* ↑ [MEDIACAPTURE-HANDLE] ↑ */

private js_properties:
    DEFINE_GETTER(kind, ext::string_view);
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(label, ext::string_view);

    DEFINE_GETTER(enabled, ext::boolean);
    DEFINE_GETTER(muted, ext::boolean);
    DEFINE_GETTER(ready_state, detail::media_stream_track_state_t);

    DEFINE_GETTER(device_id, ext::string_view);
    DEFINE_GETTER(facing_mode, ext::string_view);
    DEFINE_GETTER(group_id, ext::string_view);

    DEFINE_SETTER(enabled, ext::boolean);
};


#endif //SBROWSER2_MEDIA_STREAM_TRACK_HPP
