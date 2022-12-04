#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING__TYPEDEFS_HPP





#include "ext/string.hpp"
#include "ext/tuple.ixx"

namespace encoding::detail
{
    struct encoding_t;
    struct encoder_decoder_t;
    struct encoder_t;
    struct decoder_t;
    struct utf8_encoder_t;
    struct utf8_decoder_t;

    enum class handle_state_t {FINISHED, ERROR, CONTINUE};
    enum class encoder_error_mode_t {FATAL, HTML};
    enum class decoder_error_mode_t {REPLACEMENT, FATAL};

    using item_t = ext::string::value_type;
    using io_queue_t = ext::queue<item_t>;
    using text_decoder_options_t = ext::map<ext::string, ext::any>;
    using text_decode_options_t = ext::map<ext::string, ext::any>;
    using text_encoder_encoder_into_result_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING__TYPEDEFS_HPP
