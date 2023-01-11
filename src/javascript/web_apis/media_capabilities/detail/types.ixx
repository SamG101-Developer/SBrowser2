module;
#include "ext/macros.hpp"


export module apis.media_capabilities.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(media_capabilities)
{
    using media_configuration_t = ext::map<ext::string, ext::any>;
    using media_decoding_configuration_t = ext::map<ext::string, ext::any>;
    using media_encoding_configuration_t = ext::map<ext::string, ext::any>;
    using audio_configuration_t = ext::map<ext::string, ext::any>;
    using video_configuration_t = ext::map<ext::string, ext::any>;
    using media_capabilities_key_system_configuration_t = ext::map<ext::string, ext::any>;
    using key_system_track_configuration_t = ext::map<ext::string, ext::any>;
    using media_capabilities_info_t = ext::map<ext::string, ext::any>;
    using media_capabilities_decoding_info_t = ext::map<ext::string, ext::any>;
    using media_capabilities_encoding_info_t = ext::map<ext::string, ext::any>;

    enum class media_decoding_type_t {FILE, MEDIA_SOURCE, WEBRTC};
    enum class media_encoding_type {RECORD, WEBRTC};
    enum class hdr_metadata_type_t {SMPTE_ST2086, SMPTE_ST2094_10, SMPTE_ST2094_40};
    enum class color_gamut_t {SRGB, P3, REC2020};
    enum class transfer_function_t {SRGB, PQ, HLG};

}
