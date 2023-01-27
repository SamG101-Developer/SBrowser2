module;
#include "ext/macros.hpp"


module apis.streams.readable_stream_default_reader;
import apis.streams.readable_stream;
import apis.streams.detail;
import apis.streams.types;

import apis.dom.detail;
import apis.dom.types;
import apis.web_idl::detail;

import ext.js;
import js.env.realms;


streams::readable_stream_default_reader::readable_stream_default_reader(streams::readable_stream* stream)
{
    // The constructor is being called as the way to initialzie the class )ie not through a free function `create_...`,
    // so only call the `setup_...` method on this class.
    detail::setup_readable_stream_default_reader(this, stream);
}


auto streams::readable_stream_default_reader::read(
        ext::array_buffer_view&& view)
        -> ext::promise<readable_stream_read_result_t>
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    // If there is no stream in this ReadableStreamDefaultReader, then throw a TypeError exception, because it is not
    // possible to read from a non-existent stream.
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->stream;},
            u8"Can not read with a ReadableStreamDefaultReader if the [[stream]] slot is empty", e);

    // Create the promise that will be resolved / rejeected in the future from one of the steps in the read request
    // created below.
    auto promise = ext::promise<readable_stream_read_result_t>{};

    // Create a read request whose: chunk steps are resolving the promise with the chunk, speicifying its incomplete;
    // close steps are to resolve the promise with an empty string, specifying its done; and error steps are to reject
    // the promise.
    auto read_request = std::make_unique<detail::read_request_t>();
    read_request->chunk_steps = [&promise](auto&& chunk) {web_idl::detail::resolve_promise(promise, readable_stream_read_result_t{{u"value", chunk}, {u"done", false}})};
    read_request->close_steps = [&promise](auto&&      ) {web_idl::detail::resolve_promise(promise, readable_stream_read_result_t{{u"value", u""}, {u"done", true}})};
    read_request->error_steps = [&promise](auto&& error) {web_idl::detail::reject_promise(promise, error)};

    // Perform the default read steps on the read request and this ReadableStreamDefaultReader. Return the promise that
    // will be modified from the read request.
    detail::readable_stream_default_reader_read(this, std::move(read_request));
    return promise;
}


auto streams::readable_stream_default_reader::release_lock() -> void
{
    ACCESS_PIMPL;

    // Cannot release a lock if there is no stream, so retrun early. Otherwise, release the lock by calling the detail
    // function which performance the release functionality.
    return_if (!d->stream);
    detail::readable_stream_default_reader_release(this);
}
