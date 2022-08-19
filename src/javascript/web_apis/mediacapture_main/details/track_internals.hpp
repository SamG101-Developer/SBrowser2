#pragma once
#ifndef SBROWSER2_TRACK_INTERNALS_HPP
#define SBROWSER2_TRACK_INTERNALS_HPP

#include "ext/string.hpp"
namespace mediacapture::main {class media_stream_track;}


namespace mediacapture::detail
{
    auto track_ends_for_any_reason_except_stop(
            mediacapture::main::media_stream_track* track)
            -> void;

    auto device_permission_revocation_algorithm(
            ext::string_view permission_name,
            ext::string_view device_id)
            -> void;
};


#endif //SBROWSER2_TRACK_INTERNALS_HPP
