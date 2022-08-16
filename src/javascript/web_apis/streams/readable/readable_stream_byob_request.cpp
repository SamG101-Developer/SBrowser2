#include "readable_stream_byob_request.hpp"

#include "dom/detail/exception_internals.hpp"


auto streams::readable::readable_stream_byob_request::respond(
        const ext::number<ulonglong>& bytes_written)
        -> void
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
    [this] {return s_view.ByteLength() == 0 || s_view.Buffer()->ByteLength() == 0},
            "Cannot enqueue to a ReadableByteStreamController with an view");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !s_controller;},
            "Cannot enqueue to a ReadableByteStreamController that doesn't have a controller");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return s_view.Buffer().IsEmpty();}, // TODO : IsEmpty() correct?
            "Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    detail::readable_byte_stream_controller_response(s_controller, bytes_written);
}


auto streams::readable::readable_stream_byob_request::respond_with_new_view(
        v8::Local<v8::ArrayBufferView> view)
        -> void
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !s_controller;},
            "Cannot enqueue to a ReadableByteStreamController that doesn't have a controller");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return s_view.Buffer().IsEmpty();}, // TODO : IsEmpty() correct?
            "Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    return detail::readable_byte_stream_controller_response_with_new_view(s_controller, view);
}
