#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_TRACK_HPP
#define SBROWSER2_MEDIA_STREAM_TRACK_HPP

#include "dom/nodes/event_target.hpp"
#include "mediacapture_main/mixins/constrainable.hpp"
namespace mediacapture::main {class media_stream_track;}

#include <future>
namespace mediacapture::detail::source_internals {template <inherit<main::media_stream_track> T> struct media_stream_track_source;}

class mediacapture::main::media_stream_track
        : public dom::nodes::event_target
        , public mixins::constrainable
{
public constructors:
    media_stream_track();

private constructors:
    template <inherit<media_stream_track> T>
    media_stream_track(detail::source_internals::media_stream_track_source<T>& source, ext::boolean_view tie_source_to_context = true);

public js_methods:
    auto clone() const -> media_stream_track;
    auto stop() -> void;

public js_properties:
    ext::property<ext::string> kind;
    ext::property<ext::string> id;
    ext::property<ext::string> label;

    ext::property<ext::boolean> enabled;
    ext::property<ext::boolean> muted;
    ext::property<ext::string> ready_state;

    ext::property<ext::string> device_id;
    ext::property<ext::string> facing_mode;
    ext::property<ext::string> group_id;

private cpp_properties:
    detail::source_internals::media_stream_track_source<media_stream_track>& m_source;

private cpp_accessors:
    auto set_muted(ext::boolean_view val) -> void;
};


#endif //SBROWSER2_MEDIA_STREAM_TRACK_HPP
