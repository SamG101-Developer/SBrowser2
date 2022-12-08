#include "text_decoder.hpp"
#include "text_decoder_private.hpp"




#include "encoding/_typedefs.hpp"
#include "encoding/detail/encoding_internals.hpp"


encoding::text_decoder::text_decoder(
        ext::string_view label,
        detail::text_decoder_options_t&& options)
{
    ACCESS_PIMPL(text_decoder);
    using enum v8_primitive_error_t;

    decltype(auto) encoding = detail::get_encoding(label);
    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [e = encoding.get()] {return !e; /* || TODO */},
            u8"Failure while getting encoding");

    d->encoding = std::move(encoding);
    d->error_mode = options[u8"fatal"].to<ext::boolean>() ? detail::decoder_error_mode_t::FATAL : detail::decoder_error_mode_t::REPLACEMENT;
    d->ignore_bom = options[u8"ignoreBOM"].to<ext::boolean>();
}


auto encoding::text_decoder::decode(
        v8::Local<v8::BufferSource> input,
        detail::text_decode_options_t&& options)
{
    ACCESS_PIMPL(text_decoder);
    using enum v8_primitive_error_t;

    if (!d->do_not_flush)
    {
        d->decoder = std::move(d->encoding->decoder);
        d->io_queue = detail::io_queue_t{};
        d->bom_seen = false;
    }

    d->do_not_flush = options[u8"stream"].to<ext::boolean>();
    for (ptrdiff_t i = 0; i < input->Buffer()->GetBackingStore()->ByteLength(); ++i)
        d->io_queue.push(input->Buffer()->GetBackingStore().get()[i]);
    auto output = detail::io_queue_t{};

    while (true)
    {
        decltype(auto) item = d->io_queue.front();
        if (d->io_queue.empty())
            return detail::serialize_io_queue(this, output);

        else
        {
            auto result = detail::process_item(item, *d->decoder, d->io_queue, output, d->error_mode);
            return_if (result.has_value() && *result == detail::handle_state_t::FINISHED) detail::serialize_io_queue(this, output);

            dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
                    [result] {return !result.has_value();},
                    u8"Error processing item");
        }
    }
}
