#include "configuration_internals.hpp"

#include "ext/hashing.hpp"
#include "ext/any.hpp"

#include USE_INNER_TYPES(media_capabilities)

#include "mimesniff/detail/mimetype_internals.hpp"

#include <range/v3/algorithm/contains.hpp>


auto media::detail::is_valid_media_configuration(
        media_configuration_t&& configuration)
        -> ext::boolean
{
    return_if (configuration.contains("audio") && is_valid_audio_configuration(configuration["audio"].to<audio_configuration_t>())) true;
    return_if (configuration.contains("video") && is_valid_video_configuration(configuration["video"].to<video_configuration_t>())) true;
    return false;
}


auto media::detail::is_valid_media_decoding_configuration(
        media_decoding_configuration_t&& configuration)
        -> ext::boolean
{
    if (configuration.contains("keySystemConfiguration"))
    {
        auto allowed_key_system_configurations = {media_decoding_type_t::FILE, media_decoding_type_t::MEDIA_SOURCE};
        auto key_system_configuration = configuration["keySystemConfiguration"].to<detail::media_capabilities_key_system_configuration_t>();
        auto key_system_configuration_type = key_system_configuration["type"].to<ext::string>();
        auto cast_type = magic_enum::enum_cast<detail::media_decoding_type_t>(key_system_configuration_type);

        return is_valid_media_configuration(std::move(configuration))
                && ranges::contains(allowed_key_system_configurations, cast_type)
                && key_system_configuration.contains("audio") == configuration.contains("audio")
                && key_system_configuration.contains("video") == configuration.contains("video");
    }

    return is_valid_media_configuration(std::move(configuration));
}


auto media::detail::is_valid_audio_mime_type(
        ext::string_view mime_type)
        -> ext::boolean
{
    auto allowed_audio_types = {"audio", "application"};
    return mimesniff::detail::valid_mime_type(mime_type)
            && ranges::contains(allowed_audio_types, mimesniff::detail::parse_mime_type(mime_type)->type);
}


auto media::detail::is_valid_video_mime_type(
        ext::string_view mime_type)
        -> ext::boolean
{
    auto allowed_video_types = {"video", "application"};
    return mimesniff::detail::valid_mime_type(mime_type)
            && ranges::contains(allowed_video_types, mimesniff::detail::parse_mime_type(mime_type)->type);
}


auto media::detail::is_valid_audio_configuration(
        audio_configuration_t&& configuration)
        -> ext::boolean
{
    return is_valid_audio_mime_type(configuration.try_emplace("contentType").first->second.to<ext::string>());
}


auto media::detail::is_valid_video_configuration(
        video_configuration_t&& configuration)
        -> ext::boolean
{
    return is_valid_video_mime_type(configuration.try_emplace("contentType").first->second.to<ext::string>())
            && configuration.try_emplace("framerate").first->second.to<ext::number<double>>() < 0
            && configuration.try_emplace("framerate").first->second.to<ext::number<double>>() == ext::number<double>::inf();
}


auto media::detail::create_media_capabilities_decoding_info(
        media_decoding_configuration_t&& configuration)
        -> media_capabilities_decoding_info_t
{
    auto key_system_access =
            configuration.contains("keySystemAccess") && check_encrypted_decoding_support(std::move(configuration))
            || !configuration.contains("keySystemAccess") && can_decode_media(std::move(configuration));

    return detail::media_capabilities_decoding_info_t
    {
        {"configuration", auto{configuration}},
        {"keySystemAccess", std::move(key_system_access)},
        {"smooth", true}, // TODO
        {"powerEfficient", true} // TODO
    };
}


auto media::detail::create_media_capabilities_encoding_info(
        media_encoding_configuration_t&& configuration)
        -> media_capabilities_encoding_info_t
{
    return detail::media_capabilities_encoding_info_t
    {
        {"configuration", auto{configuration}},
        {"supported", true}, // TODO
        {"smooth", true}, // TODO
        {"powerEfficient", true} // TODO
    };
}
