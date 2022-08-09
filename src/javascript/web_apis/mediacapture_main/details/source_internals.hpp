#pragma once
#ifndef SBROWSER2_SOURCE_INTERNALS_HPP
#define SBROWSER2_SOURCE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"

#include <v8-local-handle.h>
#include <v8-object.h>

namespace mediacapture::main {class media_stream_track;}

namespace mediacapture::detail::source_internals
{
    template <inherit<main::media_stream_track> T = main::media_stream_track>
    struct media_stream_track_source;

    template <inherit<main::media_stream_track> T>
    auto initialize_underlying_source(
            main::media_stream_track* track,
            media_stream_track_source<T>& source)
            -> void;

    template <inherit<main::media_stream_track> T>
    auto tie_track_source_to_context(
            media_stream_track_source<T>& source)
            -> void;

    auto stop_all_sources(
            v8::Local<v8::Object> global_object)
            -> void;
};


template <inherit<mediacapture::main::media_stream_track> T>
struct mediacapture::detail::source_internals::media_stream_track_source
{
    using source_type = T;
    ext::function<void(main::media_stream_track*)> source_specific_construction_steps;
    ext::function<void(main::media_stream_track*, main::media_stream_track*)> source_specific_cloning_steps;

    ext::string label;
    ext::boolean muted;
};


#endif //SBROWSER2_SOURCE_INTERNALS_HPP
