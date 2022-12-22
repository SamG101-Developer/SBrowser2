module;
#include "ext/macros/language_shorthand.hpp"
#include <swl/variant.hpp>
#include <tuplet/tuple.hpp>


module apis.encoding.detail;
import apis.encoding.types;

import ext.core;


auto encoding::detail::io_queue_read(io_queue_t& queue) -> item_t
{
    while (queue.empty()) continue;
    decltype(auto) item = std::move(queue.front());
    return_if (item == end_of_queue) end_of_queue;

    queue |= ranges::actions::pop();
    return item;
}



auto encoding::detail::process_queue(
        encoder_decoder_t& encoder_decoder,
        io_queue_t& input,
        io_queue_t& output,
        ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode)
        -> ext::expected <handle_state_t>
{
    using namespace ext::literals;
    while (true)
    {
        auto result = process_item(io_queue_read(input), encoder_decoder, input, output, std::move(mode));
        if (result.has_value() && !(*result)[1_tag] == handle_state_t::CONTINUE) return result;
    }
}


encoding::detail::
