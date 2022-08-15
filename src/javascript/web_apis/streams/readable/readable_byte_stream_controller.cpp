#include "readable_byte_stream_controller.hpp"

#include "dom/detail/exception_internals.hpp"

#include "streams/_typedefs.hpp"
#include "streams/readable/readable_stream.hpp"

#include <v8-array-buffer.h>


auto streams::readable::readable_byte_stream_controller::close()
        -> void
{
    using detail::readable_stream_state_t;

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return s_close_requested;},
            "Can not close a ReadableByteStreamController that is already closing");

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return s_stream && s_stream->s_state != readable_stream_state_t::READABLE;;},
            "Can not close a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    detail::abstract_operations_internals::readable_byte_Stream_controller_close(this);
}


auto streams::readable::readable_byte_stream_controller::enqueue(
        v8::Local<v8::ArrayBufferView> chunk)
        -> void
{
    using detail::readable_stream_state_t;

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [&chunk] {return chunk->ByteLength() == 0 || chunk->Buffer()->ByteLength() == 0},
            "Cannot enqueue to a ReadableByteStreamController with an empty chunk");

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return s_close_requested;},
            "Cannot enqueue to a ReadableByteStreamController that is already closing");

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return s_stream && s_stream->s_state != readable_stream_state_t::READABLE;},
            "Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    return detail::absrtact_operations_internals::readable_byte_stream_controller_enqueue(this, chunk);
}


auto streams::readable::readable_byte_stream_controller::error(
        ext::any&& error)
        -> void
{
    detail::abstract_operations_internals::readable_byte_stream_controller_error(this, std::move(error));
}


auto streams::readable::readable_byte_stream_controller::get_byob_request()
        const -> readable_stream_byob_request*
{
    return detail::abstract_operations_internals::readable_byte_stream_controller_get_byob_request();
}


auto streams::readable::readable_byte_stream_controller::get_desired_size()
        const -> ext::number<double>
{
    return detail::abstract_operations_internals::readable_byte_stream_controller_get_desired_size();
}


auto streams::readable::readable_byte_stream_controller::s_pull_steps(
        const detail::read_request_t& request)
        -> void
{
    ASSERT(detail::abstract_operations_internals::readable_stream_has_default_reader(s_stream));
    if (s_queue_total_size > 0)
    {
        ASSERT(detail::abstract_operations_internals::readable_stream_get_num_read_requests(s_stream) == 0);
        detail::abstract_operations_internals::readable_byte_stream_controller_fill_read_request_from_queue(this, request);
        return;
    }

    if (s_auto_allocate_chunk_size)
    {
        JS_REALM_GET_RELEVANT(this)
        auto buffer = v8::ArrayBuffer::New(this_relevant_agent, s_auto_allocate_chunk_size);
        if (buffer.IsEmpty())
        {
            request.error_steps(buffer);
            return;
        }

        using detail::readable_stream_reader_mode_t;
        s_pending_pull_intos.emplace_back(
            buffer, s_auto_allocate_chunk_size, 0, s_auto_allocate_chunk_size, 0, 1, v8::DataView::New(buffer, 0, 0),
            readable_stream_reader_mode_t::DEFAULT);
    }

    detail::abstract_operations_internals::readable_stream_add_read_request(stream, read_request);
    detail::abstract_operations_internals::readable_byte_stream_controler_call_pull_if_needed(this);
}


auto streams::readable::readable_byte_stream_controller::s_cancel_steps(
        ext::any&& reason)
        -> void
{
    detail::abstract_operations_internals::readable_byte_stream_controller_clear_pending_pull_intos(this);
    detail::queue_internals::reset_queue(this);

    auto result = s_cancel_steps(std::move(reason));
    detail::abstract_operations_internals::readable_byte_stream_controller_clear_algorithms();
    return result;
}


auto streams::readable::readable_byte_stream_controller::s_release_steps()
        -> void
{
    if (!s_pending_pull_intos.empty())
    {
        using detail::readable_stream_reader_mode_t;

        decltype(auto) first_pending_ull_into = s_pending_pull_intos[0];
        first_pending_ull_into.reader_type = readable_stream_reader_mode_t::NONE;
        s_pending_pull_intos = {first_pending_ull_into};
    }
}