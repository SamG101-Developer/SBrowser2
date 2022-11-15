#include "readable_stream_byob_request.hpp"
#include "readable_stream_byob_request_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "streams/detail/readable_abstract_operations_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"


auto streams::readable::readable_stream_byob_request::respond(ext::number<ulonglong> bytes_written) -> void
{
    ACCESS_PIMPL(readable_stream_byob_request);
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d, &e] {return web_idl::detail::byte_length(d->view, e.js.realm()) == 0 || web_idl::detail::byte_length(web_idl::detail::viewed_buffer(d->view), e.js.realm()) == 0},
            u8"Cannot enqueue to a ReadableByteStreamController with an view");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->controller;},
            u8"Cannot enqueue to a ReadableByteStreamController that doesn't have a controller");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d, &e] {return web_idl::detail::byte_length(d->view, e.js.realm()) == 0;}, // TODO : check
            u8"Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    detail::readable_byte_stream_controller_respond(d->controller.get(), bytes_written);
}


auto streams::readable::readable_stream_byob_request::respond_with_new_view(ext::array_buffer_view&& view) -> void
{
    ACCESS_PIMPL(readable_stream_byob_request);
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->controller;},
            u8"Cannot enqueue to a ReadableByteStreamController that doesn't have a controller");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d, &e] {return web_idl::detail::byte_length(d->view, e.js.realm()) == 0;}, // TODO : check
            u8"Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state");

    return detail::readable_byte_stream_controller_response_with_new_view(d->controller.get(), view);
}
