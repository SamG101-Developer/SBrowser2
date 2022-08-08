#pragma once
#ifndef SBROWSER2_MEDIA_STREAM_TRACK_HPP
#define SBROWSER2_MEDIA_STREAM_TRACK_HPP

#include "dom/nodes/event_target.hpp"
namespace mediacapture::main {class media_stream_track;}

#include <future>
namespace mediacapture::detail::source_internals {template <inherit<main::media_stream_track> T> struct media_stream_track_source;}

class mediacapture::main::media_stream_track
        : public dom::nodes::event_target
{
public constructors:
    media_stream_track();

private constructors:
    template <inherit<media_stream_track> T>
    media_stream_track(detail::source_internals::media_stream_track_source<T>& source, ext::boolean_view tie_source_to_context = true);

public js_methods:
    auto clone() const -> media_stream_track*;
    auto stop() -> void;
    auto get_capabilities() const -> ext::map<ext::string, ext::any>;
    auto get_constraints() const -> ext::map<ext::string, ext::any>;
    auto get_settings() const -> ext::map<ext::string, ext::any>;
    auto apply_constraints(ext::map_view<ext::string, ext::any> constraints = {}) -> std::promise<void>;

public js_properties:
    ext::property<ext::string> kind;
    ext::property<ext::string> id;
    ext::property<ext::string> label;

    ext::property<ext::boolean> enabled;
    ext::property<ext::boolean> muted;
    ext::property<ext::string> ready_state;

private cpp_properties:
    // TODO : detail::...source attribute (templated though?)
};


#endif //SBROWSER2_MEDIA_STREAM_TRACK_HPP
