module;
#include "ext/macros/pimpl.hpp"
#include <tuplet/tuple.hpp>


export module apis.encoding.types;
import apis.infra.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(encoding)
{
    class text_decoder_common;
    class text_encoder_common;

    class text_decoder;
    class text_decoder_stream;
    class text_encoder;
    class text_encoder_stream;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(encoding)
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

    using item_t = infra::detail::code_point_t;
    using io_queue_t = ext::vector<item_t>;
    using text_decoder_options_t = ext::map<ext::string, ext::any>;
    using text_decode_options_t = ext::map<ext::string, ext::any>;
    using text_encoder_encoder_into_result_t = ext::map<ext::string, ext::any>;
    using handler_result_t = ext::tuple<handle_state_t, ext::vector<item_t>>;
}


struct encoding::detail::encoding_t
{
    virtual ~encoding_t();

    ext::string name;
    ext::vector<ext::string> labels;
    ext::map<infra::detail::code_point_t, ext::byte_t> mapping;

    std::unique_ptr<encoder_t> encoder;
    std::unique_ptr<decoder_t> decoder;
};


struct encoding::detail::encoder_decoder_t
{
    handle_state_t state;
    virtual auto handler_algorithm(io_queue_t& io_queue, item_t item) -> handler_result_t;
};


struct encoding::detail::encoder_t : public encoder_decoder_t {};
struct encoding::detail::decoder_t : public encoder_decoder_t {};
struct encoding::detail::utf8_encoder_t : public encoder_t {};
struct encoding::detail::utf8_decoder_t : public decoder_t {};
