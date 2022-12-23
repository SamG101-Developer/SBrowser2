module;
#include "ext/macros/language_shorthand.hpp"
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/to_container.hpp>
#include <swl/variant.hpp>
#include <tuplet/tuple.hpp>


module apis.encoding.detail;
import apis.encoding.types;
import apis.encoding.mixins.text_decoder_common;
import apis.encoding.mixins.text_decoder_common_private;

import apis.infra.detail;
import ext.core;


auto encoding::detail::io_queue_read(io_queue_t& queue) -> item_t
{
    while (queue.empty()) continue;
    decltype(auto) item = std::move(queue.front());
    return_if (item == end_of_queue) end_of_queue;

    queue |= ranges::actions::pop_front();
    return item;
}


auto encoding::detail::process_queue(
        encoder_decoder_t& encoder_decoder,
        io_queue_t& input,
        io_queue_t& output,
        ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode)
        -> ext::expected<item_t>
{
    using namespace ext::literals;
    while (true)
    {
        auto result = process_item(io_queue_read(input), encoder_decoder, input, output, std::move(mode));
        return_if (ext::holds_alternative<item_t>(result)) ext::unsafe_get<item_t>(result);
    }
}


auto encoding::detail::process_item(
        char16_t item,
        encoder_decoder_t& encoder_decoder,
        io_queue_t& input,
        io_queue_t& output,
        ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode)
        -> ext::variant<item_t, handle_state_t>
{
    ext::assert_(dynamic_cast<encoder_t*>(&encoder_decoder) && mode != decoder_error_mode_t::REPLACEMENT);
    ext::assert_(dynamic_cast<decoder_t*>(&encoder_decoder) && mode != encoder_error_mode_t::HTML);
    ext::assert_(dynamic_cast<encoder_t*>(&encoder_decoder) && !infra::detail::is_surrogate(item));

    using namespace ext::literals;
    auto result = encoder_decoder.handler_algorithm(input, item);
    if (result[0_tag] == handle_state_t::FINISHED)
    {
        io_queue_push(output, end_of_queue);
        return result;
    }

    else if (!result[1_tag].empty())
    {
        ext::assert_(dynamic_cast<decoder_t*>(&encoder_decoder) && !ranges::any_of(result[1_tag], &infra::detail::is_surrogate));
        io_queue_push(output, result[1_tag]);
    }

    else if (result[0_tag] == handle_state_t::ERROR)
    {
        if (mode == decoder_error_mode_t::REPLACEMENT) io_queue_push(output, 0xfffd);
        if (mode == encoder_error_mode_t::HTML) io_queue_push_n(output, {0x26, 0x23, /* TODO */ 0x3b});
        else return result;
    }

    return handle_state_t::CONTINUE;
}


auto encoding::detail::get_encoding(ext::string&& label) -> std::unique_ptr<encoding_t>
{
    auto encoding = std::make_unique<encoding>();
    encoding->name = "utf-8";
    encoding->encoder = std::make_unique<utf8_encoder>();
    encoding->decoder = std::make_unique<utf8_decoder>();
}


auto encoding::detail::serialize_io_queue(text_decoder_common* decoder, io_queue_t& io_queue) -> ext::string
{
    auto output = ext::string{};
    while (true)
    {
        auto item = io_queue_read(io_queue);
        return_if (item == end_of_queue) output;

        if (decoder->d_func()->encoding->name == "utf-8" && !decoder->d_func()->ignore_bom && !decoder->d_func()->seen_bom)
        {
            decoder->d_func()->bom_seen = true;
            continue_if (item == 0xfeff);
        }

        output.emplace_back(*item);
    }
}


auto encoding::detail::utf8_decode(io_queue_t& io_queue, io_queue_t&& output) -> io_queue_t
{
    auto buffer = io_queue_peek_n(io_queue, 3) | ranges::to<ext::byte_string>();
    if (ext::sequence_matches(std::move(buffer)), 0xef, 0xbb, 0xbf)
        static_cast<void>(io_queue_read_n(io_queue, 3));

    auto encoding = get_encoding();
    process_queue(*encoding->decoder, io_queue, output, decoder_error_mode_t::REPLACEMENT);
    return output;
}


auto encoding::detail::utf8_decode_without_bom(io_queue_t& io_queue, io_queue_t&& output) -> io_queue_t
{
    auto encoding = get_encoding();
    process_queue(*encoding->decoder, io_queue, output, decoder_error_mode_t::REPLACEMENT);
    return output;
}


auto encoding::detail::utf8_decode_without_bom_or_fail(io_queue_t& io_queue, io_queue_t&& output ) -> ext::expected<io_queue_t>
{
    auto encoding = get_encoding();
    auto potential_error = process_queue(*encoder->decoder, io_queue, output, dedocer_error_mode_t::FATAL);
    return potential_error.has_value() ? output : potential_error.error();
}


auto encoding::detail::utf8_encode(io_queue_t& io_queue, io_queue_t&& output) -> io_queue_t
{
    encoding = get_encoding();
    process_queue(*encoding->encoder, io_queue, output, encoder_error_mode_t::HTML);
    return output;
}
