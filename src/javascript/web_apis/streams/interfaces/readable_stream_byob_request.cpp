module;
#include "ext/macros.hpp"


module apis.streams.readable_stream_byob_request;

import js.env.env;


auto streams::readable_stream_byob_request::respond(ext::number<ulonglong> bytes_written) -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d, &e] {return web_idl::detail::byte_length(d->view, e.js.realm()) == 0 || web_idl::detail::byte_length(web_idl::detail::viewed_buffer(d->view), e.js.realm()) == 0},
            u8"Cannot enqueue to a ReadableByteStreamController with an view", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->controller;},
            u8"Cannot enqueue to a ReadableByteStreamController that doesn't have a controller", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d, &e] {return web_idl::detail::byte_length(d->view, e.js.realm()) == 0;}, // TODO : check
            u8"Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state", e);

    detail::readable_byte_stream_controller_respond(d->controller.get(), bytes_written);
}


auto streams::readable_stream_byob_request::respond_with_new_view(ext::array_buffer_view&& view) -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->controller;},
            u8"Cannot enqueue to a ReadableByteStreamController that doesn't have a controller", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d, &e] {return web_idl::detail::byte_length(d->view, e.js.realm()) == 0;}, // TODO : check
            u8"Cannot enqueue to a ReadableByteStreamController that's [[stream]] isn't in the READABLE state", e);

    return detail::readable_byte_stream_controller_response_with_new_view(d->controller.get(), view);
}
