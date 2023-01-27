module;
#include "ext/macros.hpp"


module apis.streams.readable_stream_byob_reader;
import apis.streams.readable_stream;
import apis.streams.detail;

import apis.web_idl.detail;

import js.env.realms;
import ext.js;


streams::readable_stream_byob_reader::readable_stream_byob_reader(readable_stream* stream)
{
    detail::setup_readable_stream_byob_reader(this, stream);
}


auto streams::readable_stream_byob_reader::read(
        ext::array_buffer_view&& view)
        -> ext::promise<readable_stream_read_result_t>
{
    ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);

    if (web_idl::detail::byte_length(view, e.js.realm()) == 0
            || web_idl::detail::byte_length(web_idl::detail::viewed_buffer(view), e.js.realm()) == 0
            || !web_idl::detail::is_detached(web_idl::detail::viewed_buffer(view), e.js.realm())
            || !d->stream)
        return web_idl::detail::create_rejected_promise<readable_stream_read_result_t>(v8::Exception::TypeError());

    auto promise = ext::promise<readable_stream_read_result_t>{};
    auto read_into_request = std::make_unique<detail::read_into_request_t>();
    read_into_request->chunk_steps = [&promise](auto&& chunk) {promise.set_value(readable_stream_read_result_t{{"value", chunk}, {"done", false}});};
    read_into_request->close_steps = [&promise](auto&& chunk) {promise.set_value(readable_stream_read_result_t{{"value", chunk}, {"done", true}});};
    read_into_request->error_steps = [&promise](auto&& error) {promise.set_exception(error);};

    detail::readable_stream_byob_reader_read(this, view, std::move(view), std::move(read_into_request));
    return promise;
}


auto streams::readable_stream_byob_reader::release_lock() -> void
{
    ACCESS_PIMPL;
    return_if (!d->stream);
    detail::readable_stream_byob_reader_release(this);
}
