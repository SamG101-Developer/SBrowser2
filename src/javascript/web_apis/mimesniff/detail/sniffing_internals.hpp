#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_SNIFFING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_SNIFFING_INTERNALS_HPP


#include USE_INNER_TYPES(mimesniff)

namespace mimesniff::detail::sniffing_internals
{
    auto sniff_images_specifically(
            const resource_t& resource)
            -> void;

    auto sniff_audio_or_video_specifically(
            const resource_t& resource)
            -> void;

    auto sniff_in_plugin_context(
            const resource_t& resource)
            -> void;

    auto sniff_in_style_context(
            const resource_t& resource)
            -> void;

    auto sniff_in_script_context(
            const resource_t& resource)
            -> void;

    auto sniff_in_font_context(
            const resource_t& resource)
            -> void;

    auto sniff_in_text_track_context(
            const resource_t& resource)
            -> void;

    auto sniff_in_cache_manifest_context(
            const resource_t& resource)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_SNIFFING_INTERNALS_HPP
