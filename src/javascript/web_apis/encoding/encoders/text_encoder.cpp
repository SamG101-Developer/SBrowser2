module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"
#include <range/v3/to_container.hpp>
#include <v8-array-buffer.h>
#include <v8-container.h>
#include <v8-typed-array.h>


module apis.encoding.text_encoder;
import apis.encoding.text_encoder_private;
import apis.encoding.detail;
import apis.encoding.types;

import apis.web_idl.detail;

import ext.core;
import ext.js;


encoding::text_encoder::text_encoder()
{
    INIT_PIMPL;
}


auto encoding::text_encoder::encode(
        ext::string&& input)
        -> ext::uint8_array
{
    auto io_queue = input | ranges::to<detail::io_queue_t>();
    auto output = detail::io_queue_t{detail::end_of_queue};
    auto encoder = detail::get_encoding();

    while (true)
    {
        auto item = detail::io_queue_read(io_queue);
        auto result = detail::process_item(item, *encoder, io_queue, output, detail::encoder_error_mode_t::FATAL);
        ext::assert_(result.has_value(), "Encoding processing must be successful");

        if (*result == detail::handle_state_t::FINISHED)
        {
            auto raw_data = ext::vector<detail::item_t>{&output.front(), &output.back()};
            auto backing_store = v8::ArrayBuffer::NewBackingStore(raw_data, output.size());
            auto array_buffer = v8::ArrayBuffer::New(v8::Isolate::GetCurrent(), std::move(backing_store));
            auto uint8_array = v8::Uint8Array::New(array_buffer, 0, output.size());
        }
    }
}


auto encoding::text_encoder::encode_into(
        ext::string&& source,
        ext::uint8_array& destination)
        -> text_encoder_encoder_into_result_t
{
    using namespace ext::literals;
    auto written = ext::number{0};
    auto read = ext::number{0};

    auto encoder = detail::get_encoding();
    auto unused = detail::io_queue_t{};
    auto source_queue = detail::convert_to_queue(std::move(source));

    while (true)
    {
        auto item = detail::io_queue_read(source_queue);
        auto result = encoder.handler_algorithm(unused, item);
        break_if (result[0_tag] == detail::handle_state_t::FINISHED);
        break_if (web_idl::detail::byte_length(destination) - written < result[1_tag].size());

        read += item > 0xffff ? 2 : 1;
        auto s = web_idl::detail::byte_length(destination);
        web_idl::detail::write(result, destination, written);
        written += result.size();
    }

    return {{u"read", read}, {u"written", written}};
}
