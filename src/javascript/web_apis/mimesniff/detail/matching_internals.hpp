#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MATCHING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MATCHING_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/set.hpp"
#include USE_INNER_TYPES(mimesniff)

namespace mimesniff::detail::matching_internals
{
    auto pattern_matching_algorithm(
            char* input,
            byte_pattern_t pattern,
            pattern_mask_t mask,
            ext::set<char>&& ignore)
            -> ext::boolean;

    auto determine_matching_image_mime_type(
            char* sequence)
            -> mime_type_t;

    auto determine_matching_audio_or_video_matching_algorithm(
            char* sequence)
            -> mime_type_t;

    auto determine_matching_font_mime_type(
            char* sequence)
            -> mime_type_t;

    auto determine_matching_archive_mime_type(
            char* sequence)
            -> mime_type_t;

    auto matches_mp4_signature(
            char* sequence)
            -> ext::boolean;

    auto matches_mp3_header_signature(
            char* sequence)
            -> ext::boolean;

    auto matches_mp3_no_id3_signature(
            char* sequence)
            -> ext::boolean;

    auto matches_webm_signature(
            char* sequence)
            -> ext::boolean;

    auto match_padded_sequence(
            char* sequence,
            ext::number<size_t> offset,
            ext::number<size_t> end)
            -> ext::boolean;

    auto compute_mp3_frame_size()
            -> ext::number<size_t>;

    auto parse_mp3_frame()
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MATCHING_INTERNALS_HPP
