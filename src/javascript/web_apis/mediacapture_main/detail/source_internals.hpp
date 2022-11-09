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
#include INCLUDE_INNER_TYPES(mediacapture_main)

namespace mediacapture::main {class media_stream_track;}

namespace mediacapture::detail
{
    auto initialize_underlying_source(
            main::media_stream_track* track,
            media_stream_track_source_t& source)
            -> void;

    auto tie_track_source_to_context(
            media_stream_track_source_t& source)
            -> void;

    auto stop_all_sources(
            v8::Local<v8::Object> global_object)
            -> void;
};


struct mediacapture::detail::media_stream_track_source_t
{
    ext::string source_type;
    ext::function<void(const main::media_stream_track*)> source_specific_construction_steps;
    ext::function<void(const main::media_stream_track*, const main::media_stream_track*)> source_specific_cloning_steps;

    ext::string label;
    ext::boolean muted;
};


#endif //SBROWSER2_SOURCE_INTERNALS_HPP
