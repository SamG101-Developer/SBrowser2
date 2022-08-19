#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_DETAIL_CONFIGURATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_DETAIL_CONFIGURATION_INTERNALS_HPP

#include "ext/boolean.hpp"

#include "media_capabilities/_typedefs.hpp"

namespace media::detail
{
    auto is_valid_media_configuration(
            media_configuration_t&& configuration)
            -> ext::boolean;

    auto is_valid_media_decoding_configuration(
            media_decoding_configuration_t&& configuration)
            -> ext::boolean;

    auto create_media_capabilities_encoding_info(
            media_encoding_configuration_t&& configuration)
            -> media_capabilities_encoding_info_t;

    auto create_media_capabilities_decoding_info(
            media_decoding_configuration_t&& configuration)
            -> media_capabilities_decoding_info_t;

    auto check_encrypted_decoding_support(
            media_decoding_configuration_t&& configuration)
            -> ext::boolean;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_DETAIL_CONFIGURATION_INTERNALS_HPP
