module;
#include "ext/macros/pimpl.hpp"
#include <swl/variant.hpp>


export module apis.encoding.detail;
import apis.encoding.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(encoding)
{
    auto end_of_queue = item_t{0xffff}; // TODO : use unusable value

    auto io_queue_read(io_queue_t& queue) -> item_t;
    auto io_queue_read_n(io_queue_t& queue, ext::number<int> n) -> ext::vector<item_t>;
    auto io_queue_peek_n(io_queue_t& queue, ext::number<int> n) -> ext::vector_span<item_t>;
    auto io_queue_push(io_queue_t& queue, item_t item) -> void;
    auto io_queue_push_n(io_queue_t& queue, ext::vector_span<item_t> item) -> void;
    auto io_queue_prepend(io_queue_t& queue, item_t item) -> void;

    auto process_queue(encoder_decoder_t& encoder_decoder, io_queue_t& input, io_queue_t& output, ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode) -> ext::expected<handle_state_t>;
    auto process_item(item_t item, encoder_decoder_t& encoder_decoder, io_queue_t& input, io_queue_t& output, ext::variant<encoder_error_mode_t, decoder_error_mode_t> mode) -> ext::expected<handle_state_t>;
    auto get_encoding(ext::string_view label) -> std::unique_ptr<encoding_t>;
    auto get_output_encoding(detail::encoding_t* input_encoding) -> std::unique_ptr<detail::encoding_t>;
    auto serialize_io_queue(text_decoder_common* decoder, io_queue_t& io_queue) -> ext::string;
    auto convert_to_queue(ext::string&& queue) -> io_queue_t;
}