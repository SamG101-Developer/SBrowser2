#include "text_encoder.hpp"
#include "text_encoder_private.hpp"

#include "ext/assertion.hpp"

#include "encoding/_typedefs.hpp"
#include "encoding/detail/encoding_internals.hpp"

#include <range/v3/to_container.hpp>
#include <v8-array-buffer.h>
#include <v8-container.h>


encoding::text_encoder::text_encoder() {}


auto encoding::text_encoder::encode(
        ext::string&& input)
        -> v8::Uint8Array
{
    auto input_queue = input | ranges::to<detail::io_queue_t>();
    auto output = detail::io_queue_t{};

    while (true)
    {
        auto item = input_queue.front();
        input_queue.pop();

        auto result = detail::process_item(item, detail::utf8_encoder_t{}, input, output, detail::encoder_error_mode_t::FATAL);
        ASSERT (result.has_value(), "Encoding processing must be successful");

        if (*result == detail::handle_state_t::FINISHED)
        {
            auto raw_data = ext::vector<detail::item_t>{&output.front(), &output.back()};
            auto backing_store = v8::ArrayBuffer::NewBackingStore(raw_data, output.size());
            auto array_buffer = v8::ArrayBuffer::New(v8::Isolate::GetCurrent(), std::move(backing_store));
        }
    }
}


auto encoding::text_encoder::encode_into(
        ext::string&& source,
        v8::Local<v8::Uint8Array> destination)
        -> detail::text_encoder_encoder_into_result_t
{
    auto written = ext::number<int>{0};
    auto read = ext::number<int>{0};

    auto encoder = detail::utf8_encoder_t{};
    auto unused = detail::io_queue_t{};
    auto source_queue = detail::convert_to_queue(std::move(source));

    while (true)
    {
        auto item = source_queue.front();
        source_queue.pop();
        auto result = encoder.handler_algorithm(source_queue, item);
        return_if (result[ext::tag<0>()] == detail::handle_state_t::FINISHED) {};

        if (destination->ByteLength() - written >= result[ext::tag<1>()].size())
        {
            read += item > 0xffff ? 2 : 1;
            auto s = destination->Length();
            destination->Set(
                    v8::Isolate::GetCurrent()->GetCurrentContext(), destination->Length(),
                    v8pp::to_v8(v8::Isolate::GetCurrent(), result[ext::tag<1>()].at(destination->Length() - s)));
        }
    }
}
