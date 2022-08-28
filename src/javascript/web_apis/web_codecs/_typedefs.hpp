#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace web_codecs {class audio_data;}
namespace web_codecs::abstract {class abstract_encoder_decoder;}


namespace web_codecs::detail
{
    enum class codec_state_t {UNCONFIGURED, CONFIGURED, CLOSED};
    enum class encoded_audio_chunk_type_t {KEY, DELTA};

    using control_message_t = ext::function<void(abstract::abstract_encoder_decoder*)>;

    using audio_decoder_init_t = ext::map<ext::string, ext::any>;
    using audio_decoder_config_t = ext::map<ext::string, ext::any>;
    using audio_decoder_support_t = ext::map<ext::string, ext::any>;
    using audio_data_output_callback_t = ext::function<void(audio_data*)>;
    using encoded_audio_chunk_metadata = ext::map<ext::string, ext::any>;
    using encoded_video_chunk_metadata = ext::map<ext::string, ext::any>;
    using svc_output_metadata = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS__TYPEDEFS_HPP
