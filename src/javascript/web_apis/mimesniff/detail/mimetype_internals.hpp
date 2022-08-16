#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MIMETYPE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MIMETYPE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/set.hpp"
#include USE_INNER_TYPES(mimesniff)

namespace mimesniff::detail::mimetype_internals
{
    auto essence(
            const mime_type_t& mime_type)
            -> ext::string;

    auto mime_type_supported_by_user_agent(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto valid_mime_type(
            ext::string_view string)
            -> ext::boolean;

    auto parse_mime_type(
            ext::string input)
            -> ext::optional<mime_type_t>;

    auto serialize_mime_type(
            const mime_type_t& mime_type)
            -> ext::string;

    auto is_image_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_audio_or_video_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_font_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_zip_based_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_archive_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_xml_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_html_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_scriptable_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_javascript_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto is_json_mime_type(
            const mime_type_t& mime_type)
            -> ext::boolean;

    auto supplied_mime_type_detection_algorithm(
            const resource_t& resource)
            -> mime_type_t;

    auto read_resource_header(
            const resource_t& resource)
            -> resource_header_t;

    auto parse_vint(
            char* sequence,
            ext::number<size_t> length,
            ext::number<size_t> iter)
            -> std::tuple<ext::number<int>, ext::number<int>>;

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MIMETYPE_INTERNALS_HPP
