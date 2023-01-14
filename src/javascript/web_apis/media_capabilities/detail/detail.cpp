module;
#include "ext/macros.hpp"
#include <range/v3/algorithm/contains.hpp>
#include <magic_enum.hpp>


module apis.media_capabilities.detail;
import apis.media_capabilities.types;

import ext.core;


auto media_capabilities::detail::is_valid_media_configuration(
        media_configuration_t&& configuration)
        -> ext::boolean
{
    // If the 'configuration' contains the "audio" or "video" entry and its respective valifity check passes, then
    // return 'true', otherwise 'false'.
    return_if (configuration.contains(u"audio") && is_valid_audio_configuration(configuration[u"audio"].to<audio_configuration_t>())) true;
    return_if (configuration.contains(u"video") && is_valid_video_configuration(configuration[u"video"].to<video_configuration_t>())) true;
    return false;
}


auto media_capabilities::detail::is_valid_media_decoding_configuration(
        media_decoding_configuration_t&& configuration)
        -> ext::boolean
{
    if (configuration.contains(u"keySystemConfiguration"))
    {
        auto allowed_key_system_configurations = {media_decoding_type_t::FILE, media_decoding_type_t::MEDIA_SOURCE};
        auto key_system_configuration = configuration[u"keySystemConfiguration"].to<detail::media_capabilities_key_system_configuration_t>();
        auto key_system_configuration_type = key_system_configuration[u"type"].to<ext::string>();
        auto cast_type = magic_enum::enum_cast<media_decoding_type_t>(key_system_configuration_type);

        return is_valid_media_configuration(std::move(configuration))
                && ranges::contains(allowed_key_system_configurations, cast_type)
                && key_system_configuration.contains(u"audio") == configuration.contains(u"audio")
                && key_system_configuration.contains(u"video") == configuration.contains(u"video");
    }

    return is_valid_media_configuration(std::move(configuration));
}


auto media_capabilities::detail::is_valid_audio_mime_type(
        ext::string_view mime_type)
        -> ext::boolean
{
    auto allowed_audio_types = {u"audio", u"application"};
    return mimesniff::detail::valid_mime_type(mime_type)
            && ranges::contains(allowed_audio_types, mimesniff::detail::parse_mime_type(mime_type)->type);
}


auto media_capabilities::detail::is_valid_video_mime_type(
        ext::string_view mime_type)
        -> ext::boolean
{
    auto allowed_video_types = {u"video", u"application"};
    return mimesniff::detail::valid_mime_type(mime_type)
            && ranges::contains(allowed_video_types, mimesniff::detail::parse_mime_type(mime_type)->type);
}


auto media_capabilities::detail::is_valid_audio_configuration(
        audio_configuration_t&& configuration)
        -> ext::boolean
{
    return is_valid_audio_mime_type(configuration[u"contentType"].to<ext::string>());
}


auto media_capabilities::detail::is_valid_video_configuration(
        video_configuration_t&& configuration)
        -> ext::boolean
{
    return is_valid_video_mime_type(configuration.try_emplace(u"contentType").first->second.to<ext::string>())
            && configuration.try_emplace(u"framerate").first->second.to<ext::number<double>>() < 0
            && configuration.try_emplace(u"framerate").first->second.to<ext::number<double>>() == ext::number<double>::inf();
}


auto media_capabilities::detail::create_media_capabilities_decoding_info(
        media_decoding_configuration_t&& configuration)
        -> media_capabilities_decoding_info_t
{
    auto key_system_access =
            configuration.contains(u"keySystemAccess") && check_encrypted_decoding_support(std::move(configuration))
            || !configuration.contains(u"keySystemAccess") && can_decode_media(std::move(configuration));

    return detail::media_capabilities_decoding_info_t
    {
        {u"configuration", auto{configuration}},
        {u"keySystemAccess", std::move(key_system_access)},
        {u"smooth", true}, // TODO
        {u"powerEfficient", true} // TODO
    };
}


auto media_capabilities::detail::create_media_capabilities_encoding_info(
        media_encoding_configuration_t&& configuration)
        -> media_capabilities_encoding_info_t
{
    return detail::media_capabilities_encoding_info_t
    {
        {u"configuration", auto{std::move(configuration)}},
        {u"supported", true}, // TODO
        {u"smooth", true}, // TODO
        {u"powerEfficient", true} // TODO
    };
}
