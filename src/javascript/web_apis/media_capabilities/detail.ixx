module;
#include "ext/macros/pimpl.hpp"


export module apis.mediacapabilities.detail;
import apis.mediacapabilities.types;

import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(mediacapabilities)
{
    auto is_valid_media_configuration(media_configuration_t&& configuration) -> ext::boolean;
    auto is_valid_media_decoding_configuration(media_decoding_configuration_t&& configuration) -> ext::boolean;
    auto is_valid_audio_mime_type(ext::string_view mime_type) -> ext::boolean;
    auto is_valid_video_mime_type(ext::string_view mime_type) -> ext::boolean;
    auto is_valid_audio_configuration(audio_configuration_t&& configuration) -> ext::boolean;
    auto is_valid_video_configuration(video_configuration_t&& configuration) -> ext::boolean;
    auto create_media_capabilities_encoding_info(media_encoding_configuration_t&& configuration) -> media_capabilities_encoding_info_t;
    auto create_media_capabilities_decoding_info(media_decoding_configuration_t&& configuration) -> media_capabilities_decoding_info_t;
    auto check_encrypted_decoding_support(media_decoding_configuration_t&& configuration) -> ext::boolean;
    auto can_decode_media(media_decoding_configuration_t&& configuration) -> ext::boolean;
}
