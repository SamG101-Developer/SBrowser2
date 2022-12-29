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
    // Wait for an item ton be int eh queue if teh queue is empty (blocking operation). Once there is an item avaiable
    // (placed from aonther thread), move it uot from the front of the queue, and return if its the end of the queue (ie
    // return 'end_of_queue')
    while (queue.empty()) continue;
    decltype(auto) item = std::move(queue.front());
    return_if (item == end_of_queue) end_of_queue;

    // Otherwise, pop the item from the from of the queue, and retuen whatever the item is (separate to code above
    // because the 'end_of_queue' isn't removed from the queue).
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

    // Iterate until the return statement is called ie when the result contains an item.
    while (true)
    {
        // Set the 'result' to the resultof processing an item (the front of the input -- changes for each iteration).
        // If the result is an 'item_t' type then return it (can also be a 'handle_state_t') -- the first item that when
        // processed return an item is what is always returned.
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
    using namespace ext::literals;

    // Assert that the correct error type (encoding / decoding) is provided based on the type of the 'encoder_decoder')
    // by casting the 'encoder_decoder' and checking the 'mode's value.
    ext::assert_(dynamic_cast<encoder_t*>(&encoder_decoder) && mode != decoder_error_mode_t::REPLACEMENT);
    ext::assert_(dynamic_cast<decoder_t*>(&encoder_decoder) && mode != encoder_error_mode_t::HTML);
    ext::assert_(dynamic_cast<encoder_t*>(&encoder_decoder) && !infra::detail::is_surrogate(item));

    // Get the result from the handler algorithm of the 'encoder_decoder'. Push 'end_of_queue' to the 'output' and
    // return the 'result' if the result is FINISHED (special command to sifnify to encoders/decoders that the
    // processing is finished).
    auto result = encoder_decoder.handler_algorithm(input, item);
    if (result[0_tag] == handle_state_t::FINISHED)
    {
        io_queue_push(output, end_of_queue);
        return result[0_tag];
    }

    // If there are no items in the second part of the tuple (regardless if the special command), then assert that the
    // 'encoder_decoder' is a decoder, and push the items into the 'output' io queue.
    else if (!result[1_tag].empty())
    {
        ext::assert_(dynamic_cast<decoder_t*>(&encoder_decoder) && !ranges::any_of(result[1_tag], &infra::detail::is_surrogate));
        io_queue_push_n(output, result[1_tag]);
    }

    // If the speciall command is an ERROR, then push special bytes into the 'output' queue, depending on the 'mode',
    // and retun the ERROR special commandd too.
    else if (result[0_tag] == handle_state_t::ERROR)
    {
        if (mode == decoder_error_mode_t::REPLACEMENT) io_queue_push(output, 0xfffd);
        if (mode == encoder_error_mode_t::HTML) io_queue_push_n(output, {0x26, 0x23, /* TODO */ 0x3b});
        else return result[0_tag];
    }

    // Otherwise, tell the encoder/decoder to continue (special command CONTINUE) -- meaning that whatever was just
    // tried to be processed is to be skipped).
    return handle_state_t::CONTINUE;
}


auto encoding::detail::get_encoding(ext::string&& label) -> std::unique_ptr<encoding_t>
{
    // Create an encoding and set it's attributes to the utf-8 encoding classes (only currently supported encoding --
    // modernized -- is "utf-8").
    auto encoding = std::make_unique<encoding_t>();
    encoding->name = u"utf-8";
    encoding->encoder = std::make_unique<utf8_encoder_t>();
    encoding->decoder = std::make_unique<utf8_decoder_t>();
    return encoding;
}


auto encoding::detail::serialize_io_queue(text_decoder_common* decoder, io_queue_t& io_queue) -> ext::string
{
    // Create an output string which will hold the final serialization fo the 'io_queue;, using the 'decoder' class to#
    // decode items in the 'io_queue'.
    auto output = ext::string{};

    // Iterate until the 'end_of_queue' has been reached.
    while (true)
    {
        // Read the item from the front of the queue; if it's the 'end_of_queue', then return (break from thw while
        // loop). Otheriwse, continue the method and process the 'item' using the 'decoder'.
        auto item = io_queue_read(io_queue);
        return_if (item == end_of_queue) output;

        // Special case for BOM -- if the encoding is "utf-8" (always is) and the 'decoder' hasn't seen the bom and
        // isn't ignoring the bom, then set the 'bom_seen' to True, and move back to the top of the loop if the
        // chatracter is the special character 0xfeff. Otherwise, finish the code block in the loop.
        if (decoder->d_func()->encoding->name == "utf-8" && !decoder->d_func()->ignore_bom && !decoder->d_func()->seen_bom)
        {
            decoder->d_func()->bom_seen = true;
            continue_if (item == 0xfeff);
        }

        // Emplace the underlying value in the item into the 'output' queue.
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
