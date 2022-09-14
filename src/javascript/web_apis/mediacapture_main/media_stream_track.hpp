#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_TRACK_HPP
#define SBROWSER2_MEDIA_STREAM_TRACK_HPP

#include "dom/nodes/event_target.hpp"
#include "mediacapture_main/mixins/constrainable.hpp"
#include "html/mixins/transferable.hpp"
namespace mediacapture::main {class media_stream_track;}

#include "ext/promise.hpp"
#include USE_INNER_TYPES(mediacapture_handle)
#include USE_INNER_TYPES(mediacapture_main)


class mediacapture::main::media_stream_track
        : public dom::nodes::event_target
        , public mixins::constrainable
        , public html::mixins::transferable // TODO : transfer steps defined in mediacapture-extensions API
{
public constructors:
    media_stream_track() = delete;

private constructors:
    media_stream_track(detail::media_stream_track_source& source, ext::boolean tie_source_to_context = true);

public js_methods:
    auto clone() const -> media_stream_track;
    auto stop() -> void;

    /* MEDIACAPTURE_HANDLE */
    auto get_capture_handle() -> detail::capture_handle_t;
    auto get_supported_capture_actions() -> ext::vector_view<ext::string>;
    auto send_capture_action(detail::capture_action_t action) -> ext::promise<void>;

public js_properties:
    ext::property<ext::string> kind;
    ext::property<ext::string> id;
    ext::property<ext::string> label;

    ext::property<ext::boolean> enabled;
    ext::property<ext::boolean> muted;
    ext::property<detail::media_stream_track_state_t> ready_state;

    ext::property<ext::string> device_id;
    ext::property<ext::string> facing_mode;
    ext::property<ext::string> group_id;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    detail::media_stream_track_source& m_source;

private cpp_accessors:
    DEFINE_SETTER(muted);
};


#endif //SBROWSER2_MEDIA_STREAM_TRACK_HPP
