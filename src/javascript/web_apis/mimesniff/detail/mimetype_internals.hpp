#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MIMETYPE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MIMETYPE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "mimesniff/_typedefs.hpp"

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
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_MIMETYPE_INTERNALS_HPP
