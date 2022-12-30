module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros.hpp"
#include <range/v3/to_container.hpp>
#include <v8-array-buffer.h>
#include <v8-container.h>
#include <v8-typed-array.h>


module apis.encoding.text_encoder;
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
    // Set the 'io_queue' to the 'input' (converted to an io queue), set the 'output' to a new queue containig the
    // 'end_of_queue', and set the 'encoder' to the result of 'get_encoding(...)' (the utf-8 encoder).
    auto io_queue = detail::convert_to_queue(input);
    auto output = detail::io_queue_t{detail::end_of_queue};
    auto encoder = detail::get_encoding();

    // Iterate until the 'result' from processing erach 'item' is the special command FINISHED.
    while (true)
    {
        // Get the item from the fron of the 'io_queue', and setthe 'result' to the processing of that item with the
        // 'encoder'. Assert the result didn't result in an error -- it must contain a command foir the next step.
        auto item = detail::io_queue_read(io_queue);
        auto result = detail::process_item(item, *encoder, io_queue, output, detail::encoder_error_mode_t::FATAL);
        ext::assert_(result.has_value(), "Encoding processing must be successful");

        // If the underlying value in the 'result' is the special command FINISHED, then convert the output queue into
        // a V8 UInt8Array object. TODO
        if (*result == detail::handle_state_t::FINISHED)
        {
            auto backing_store = v8::ArrayBuffer::NewBackingStore(output.data(), output.size());
            auto array_buffer = v8::ArrayBuffer::New(v8::Isolate::GetCurrent(), std::move(backing_store));
            return v8::Uint8Array::New(array_buffer, 0, output.size());
        }
    }
}


auto encoding::text_encoder::encode_into(
        ext::string&& source,
        ext::uint8_array& destination)
        -> text_encoder_encoder_into_result_t
{
    // Intitialize the 'written' and 'read' values to 0.
    using namespace ext::literals;
    auto written = ext::number{0};
    auto read = ext::number{0};

    // Set the 'encoder' to the result of 'get_encoding(...)' (the utf-8 encoder), the 'unused' to a new queue
    // containing the 'end_of_queue', and the 'source_queue' to the 'source', converted into an io queue.
    auto encoder = detail::get_encoding();
    auto unused = detail::io_queue_t{detail::end_of_queue};
    auto source_queue = detail::convert_to_queue(std::move(source));

    // Iterate until the 'result' of processing an item is the special command FINISHED, or the number of bytes in
    // 'destination' minus the number of 'written' bytes is less that the number of items in 'result' (not enough space
    // to write the next items).
    while (true)
    {
        // Get the 'item' from teh front of the queue, and set the 'result' to the resul of processing the item. Break
        // if the result if the specuial command FINSIHED, or the number of items in the resul cannot be written into
        // the destination because there are too many bytes to wtrite..
        auto item = detail::io_queue_read(source_queue);
        auto result = encoder.handler_algorithm(unused, item);
        break_if (result[0_tag] == detail::handle_state_t::FINISHED);
        break_if (web_idl::detail::byte_length(destination) - written < result[1_tag].size());

        // Increment 'read' by 2 if the item is a greater value than 0xffff (needs moren byte space), otherwise by 1.
        // Write the 'result' into the 'destiation' at the offset 'written' (mutliple writes so have to be sequentially
        // placed in the destination).
        read += item > 0xffff ? 2 : 1;
        web_idl::detail::write(result, destination, written);
        written += result.size();
    }

    // Return a dictionary contianing the number of 'read' and 'written' bytes.
    return {{u"read", read}, {u"written", written}};
}
