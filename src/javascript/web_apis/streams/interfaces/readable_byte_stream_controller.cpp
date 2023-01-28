module;
#include "ext/macros.hpp"


module apis.streams.readable_byte_stream_controller;
import apis.streams.detail;
import apis.streams.types;

import apis.dom.detail;
import apis.dom.types;

import js.env.realms;
import ext.core;


auto streams::readable_byte_stream_controller::close() -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    using detail::readable_stream_state_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->close_requested;},
            u8"Can not close a ReadableByteStreamController that is already closing", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->stream && d->stream->s_state != detail::readable_stream_state_t::READABLE;;},
            u8"Can not close a ReadableByteStreamController that's [[stream]] isn't in the READABLE state", e);

    detail::readable_byte_stream_controller_close(this);
}


auto streams::readable_byte_stream_controller::enqueue(detail::chunk_t chunk) -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    using detail::readable_stream_state_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&chunk] {return chunk->ByteLength() == 0 || chunk->Buffer()->ByteLength() == 0},
            u8"Cannot enqueue to a ReadableByteStreamController with an empty chunk", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->close_requested;},
            u8"Cannot enqueue to a ReadableByteStreamController that is already closing", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->stream && d->stream->d_func()->state != readable_stream_state_t::READABLE;},
            u8"Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state",e );

    return detail::readable_byte_stream_controller_enqueue(this, chunk);
}


auto streams::readable_byte_stream_controller::error(ext::any&& error) -> void
{
    detail::readable_byte_stream_controller_error(this, std::move(error));
}


auto streams::readable_byte_stream_controller::get_desired_size() const -> ext::number<double>
{
    return detail::readable_byte_stream_controller_get_desired_size(this);
}


auto streams::readable_byte_stream_controller::get_byob_request() const -> readable_stream_byob_request*
{
    return detail::readable_byte_stream_controller_get_byob_request(this);
}