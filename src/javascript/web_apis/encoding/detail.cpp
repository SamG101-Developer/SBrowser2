module;
#include "ext/macros/language_shorthand.hpp"
#include <swl/variant.hpp>
#include <tuplet/tuple.hpp>


module apis.encoding.detail;
import apis.encoding.types;

import apis.infra.detail;

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


auto encoding::detail::process_item(
        char16_t item,
        encoder_decoder_t& encoder_decoder,
        io_queue_t& input,
        io_queue_t& output,
        ext::variant<encoder_error_mode_t, decoder_error_mode_t>&& mode)
        -> ext::expected <handle_state_t>
{
    ext::assert_(dynamic_cast<encoder_t*>(&encoder_decoder) && mode != decoder_error_mode_t::REPLACEMENT);
    ext::assert_(dynamic_cast<decoder_t*>(&encoder_decoder) && mode != encoder_error_mode_t::HTML);
    ext::assert_(dynamic_cast<encoder_t*>(&encoder_decoder) && !infra::detail::is_surrogate(item));

    using namespace ext::literals;
    auto result = encoder_decoder.handler_algorithm(input, item);
    if (result[0_tag] == handle_state_t::FINISHED)
    {
        output.emplace_back(end_of_queue);
        return result;
    }

    else if (!result[1_tag].empty())
    {

    }
}
