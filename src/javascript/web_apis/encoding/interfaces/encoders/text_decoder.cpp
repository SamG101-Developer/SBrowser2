module;
#include "ext/macros.hpp"


module apis.encoding.text_decoder;
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

    // Get the encoding, and throw an error if the provided 'label' created an invalid / null encoding instance -- the
    // encoding must be valid as it will be set into the private class 'encoding' attribute for all encoding from this
    // class.
    decltype(auto) encoding = detail::get_encoding(label);
    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [encoding = encoding.get()] {return !encoding;},
            u8"Failure while getting encoding", e);

    // Set the private class 'encoding' attribute to the newly created encoder (move the std::unique_ptr<T>), set the
    // 'error_mode' to FATAL if the 'options' map holds the "fatal" key and the value is True, and set the 'ignore_bom'
    // to the "ignoreBOM" option in 'options'.
    d->encoding = std::move(encoding);
    d->error_mode = options[u"fatal"] == bool ? detail::decoder_error_mode_t::FATAL : detail::decoder_error_mode_t::REPLACEMENT;
    d->ignore_bom = options[u"ignoreBOM"].to<ext::boolean>();
}


auto encoding::text_decoder::decode(
        ext::buffer_source&& input,
        text_decode_options_t&& options)
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;

    // If the decoder is not to flush, then set the private class 'decoder' to a new instance of the 'encoding's decoder
    // (user the copy constructor in the std::unique_ptr<T> creation), set the 'io_queue' a new queue that contains an
    // 'end_of_queue', and set 'bom_seen' to False.
    if (!d->do_not_flush)
    {
        d->decoder = std::make_unique<detail::decoder_t>(*d->encoding->decoder);
        d->io_queue = detail::io_queue_t{detail::end_of_queue};
        d->bom_seen = false;
    }

    // Set the private class 'do_not_flush' to the correspsonding otion in 'options', extend the current 'io_queue' by
    // the 'input' (if given), and set the output to a new queue queue that contains an 'end_of_queue'.
    d->do_not_flush = options[u8"stream"].to<ext::boolean>();
    if (!input.empty()) d->io_queue.insert(d->io_queue.end(), std::move(input));
    auto output = detail::io_queue_t{detail::end_of_queue};

    // Iterate until the return is called (ie a successful processing of the queue before the end of the queue has been
    // reached, or the (non-flushing) decoder has reached the end of the queue.
    while (true)
    {
        // Get the item from the front of the queue, and if the item is the 'end_of_queue' and the decoder isn't
        // flushing, then return a serialization of the 'output', which will just be the empty queue (with an
        // 'end_of_queue').
        auto item = detail::io_queue_read(d->io_queue);
        if (item == detail::end_of_queue && d->do_not_flush)
            return detail::serialize_io_queue(this, output);

        // Otherwise, the end of the queue hasn';'t been reached (or it has and the queu is being flushed), so process
        // the item and return a serialization of the queue if the item is the special command FINISHED. If the
        // processing failed (ie invalid item), then throw a TypeError.
        else
        {
            auto result = detail::process_item(item, *d->decoder, d->io_queue, output, d->error_mode);
            return_if (result.has_value() && *result == detail::handle_state_t::FINISHED) detail::serialize_io_queue(this, output);
            dom::detail::throw_v8_exception<V8_TYPE_ERROR>([result] {return !result.has_value();}, u8"Error processing item");
        }
    }
}
