#include "readable_byte_stream_controller.hpp"
#include "readable_byte_stream_controller_private.hpp"




#include "streams/detail/readable_abstract_operations_internals.hpp"
#include "streams/readable/readable_stream.hpp"
#include "streams/readable/readable_stream_private.hpp"
#include "streams/readable/readable_stream_byob_request.hpp"


auto streams::readable::readable_byte_stream_controller::close() -> void
{
    ACCESS_PIMPL(readable_byte_stream_controller);
    using enum v8_primitive_error_t;
    using detail::readable_stream_state_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->close_requested;},
            u8"Can not close a ReadableByteStreamController that is already closing");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->stream && d->stream->s_state != readable_stream_state_t::READABLE;;},
            u8"Can not close a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    detail::readable_byte_stream_controller_close(this);
}


auto streams::readable::readable_byte_stream_controller::enqueue(ext::any chunk) -> void
{
    ACCESS_PIMPL(readable_byte_stream_controller);
    using enum v8_primitive_error_t;
    using detail::readable_stream_state_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&chunk] {return chunk->ByteLength() == 0 || chunk->Buffer()->ByteLength() == 0},
            u8"Cannot enqueue to a ReadableByteStreamController with an empty chunk");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->close_requested;},
            u8"Cannot enqueue to a ReadableByteStreamController that is already closing");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return d->stream && d->stream->d_func()->state != readable_stream_state_t::READABLE;},
            u8"Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    return detail::readable_byte_stream_controller_enqueue(this, chunk);
}


auto streams::readable::readable_byte_stream_controller::error(ext::any error) -> void
{
    detail::readable_byte_stream_controller_error(this, std::move(error));
}


auto streams::readable::readable_byte_stream_controller::get_desired_size() const -> ext::number<double>
{
    return detail::readable_byte_stream_controller_get_desired_size(this);
}


auto streams::readable::readable_byte_stream_controller::get_byob_request() const -> readable_stream_byob_request
{
    return detail::readable_byte_stream_controller_get_byob_request(this);
}