module;
#include "ext/macros.hpp"
#include <swl/variant.hpp>


export module apis.encoding.detail;
import apis.encoding.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(encoding)
{
    // IO-Queue helpers
    auto end_of_queue = item_t{0xffff}; // TODO : use unusable value

    auto io_queue_read(io_queue_t& queue) -> item_t;
    auto io_queue_read_n(io_queue_t& queue, ext::number<int> n) -> ext::vector<item_t>;
    auto io_queue_peek_n(io_queue_t& queue, ext::number<int> n) -> ext::vector_span<item_t>;
    auto io_queue_push(io_queue_t& queue, item_t item) -> void;
    auto io_queue_push_n(io_queue_t& queue, ext::vector<item_t>&& item) -> void;
    auto io_queue_prepend(io_queue_t& queue, item_t item) -> void;

    // Abstract queue helpers
    auto process_queue(encoder_decoder_t& encoder_decoder, io_queue_t& input, io_queue_t& output, ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode) -> ext::expected<item_t>;
    auto process_item(item_t item, encoder_decoder_t& encoder_decoder, io_queue_t& input, io_queue_t& output, ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode) -> ext::variant<item_t, handle_state_t>;
    auto get_encoding(ext::string&& label = u"") -> std::unique_ptr<encoding_t>;
    auto get_output_encoding(encoding_t* input_encoding) -> std::unique_ptr<encoding_t>;
    auto serialize_io_queue(text_decoder_common* decoder, io_queue_t& io_queue) -> ext::string;
    auto convert_to_queue(ext::string&& queue) -> io_queue_t;

    // Encode/Decode helpers
    auto utf8_decode(io_queue_t& io_queue, io_queue_t&& output = {}) -> io_queue_t;
    auto utf8_decode_without_bom(io_queue_t& io_queue, io_queue_t&& output = {}) -> io_queue_t;
    auto utf8_decode_without_bom_or_fail(io_queue_t& io_queue, io_queue_t&& output = {}) -> ext::expected<io_queue_t>;
    auto utf8_encode(io_queue_t& io_queue, io_queue_t&& output = {}) -> io_queue_t;
}