module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"


module apis.encoding.text_decoder;
import apis.encoding.text_decoder_private;
import apis.encoding.detail;
import apis.encoding.types;

import apis.dom.detail;
import apis.dom.types;

import ext.core;
import ext.js;

import js.env.realms;
import js.env.module_type;


encoding::text_decoder::text_decoder(
        ext::string_view label,
        text_decoder_options_t&& options)
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    decltype(auto) encoding = detail::get_encoding(label);
    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [encoding = encoding.get()] {return !encoding;},
            u8"Failure while getting encoding", e);

    d->encoding = std::move(encoding);
    d->error_mode = options[u"fatal"].to<ext::boolean>() ? detail::decoder_error_mode_t::FATAL : detail::decoder_error_mode_t::REPLACEMENT;
    d->ignore_bom = options[u"ignoreBOM"].to<ext::boolean>();
}


auto encoding::text_decoder::decode(
        ext::buffer_source& input,
        text_decode_options_t&& options)
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;

    if (!d->do_not_flush)
    {
        d->decoder = std::make_unique<detail::decoder_t>(*d->encoding->decoder);
        d->io_queue = detail::io_queue_t{detail::end_of_queue};
        d->bom_seen = false;
    }

    d->do_not_flush = options[u8"stream"].to<ext::boolean>();
    // TODO : input
    auto output = detail::io_queue_t{detail::end_of_queue};

    while (true)
    {
        auto item = d->io_queue.front();
        if (item == detail::end_of_queue && d->do_not_flush)
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
