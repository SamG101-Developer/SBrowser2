#include "hook_internals.hpp"

#include "ext/expected.hpp"

#include "encoding/_typedefs.hpp"
#include "encoding/detail/encoding_internals.hpp"

#include <range/v3/algorithm/fold.hpp>


auto encoding::detail::utf8_decode(
        io_queue_t& io_queue,
        io_queue_t&& output)
        -> io_queue_t
{
    if (ext::sequence_matches(
            ranges::fold_left(ext::multi_peek<3>(io_queue), u8"", ext::ops::add) | ranges::to<ext::string>(),
            char8_t(0x00ef), char8_t(0x00bb), char8_t(0x00bf)))
    {
        for (auto i = 0; i < 3; ++i) io_queue.pop();
    }

    return utf8_decode_without_bom(io_queue, std::move(output));
}


auto encoding::detail::utf8_decode_without_bom(
        io_queue_t& io_queue,
        io_queue_t&& output) -> io_queue_t
{
    auto return_queue = std::move(output);
    process_queue(utf8_decoder_t{}, io_queue, return_queue, decoder_error_mode_t::REPLACEMENT);
    return return_queue;
}


auto encoding::detail::utf8_decode_without_bom_or_fail(
        io_queue_t& io_queue,
        io_queue_t&& output)
        -> ext::expected<io_queue_t>
{
    auto return_queue = std::move(output);
    auto potential_error = process_queue(utf8_decoder_t{}, io_queue, return_queue, decoder_error_mode_t::FATAL);
    return_if (!potential_error.has_value()) ext::failure_t{};
    return return_queue;
}


auto encoding::detail::utf8_encode(
        io_queue_t& io_queue,
        io_queue_t&& output)
        -> io_queue_t
{
    auto return_queue = std::move(output);
    process_queue(utf8_encoder_t{}, io_queue, return_queue, encoder_error_mode_t::HTML);
    return return_queue;
}
