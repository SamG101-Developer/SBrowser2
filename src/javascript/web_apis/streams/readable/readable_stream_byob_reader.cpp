#include "readable_stream_byob_reader.hpp"
#include "readable_stream_byob_reader_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "streams/detail/readable_abstract_operations_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"

#include <v8-exception.h>


streams::readable::readable_stream_byob_reader::readable_stream_byob_reader(
        streams::readable::readable_stream* stream)
{
    detail::setup_readable_stream_byob_reader(this, stream);
}


auto streams::readable::readable_stream_byob_reader::read(
        ext::array_buffer_view&& view)
        -> ext::promise<detail::readable_stream_read_result_t>
{
    ACCESS_PIMPL(readable_stream_byob_reader);
    auto e = js::env::env::relevant(this);

    if (web_idl::detail::byte_length(view, e.js.realm()) == 0
            || web_idl::detail::byte_length(web_idl::detail::viewed_buffer(view), e.js.realm()) == 0
            || !web_idl::detail::is_detached(web_idl::detail::viewed_buffer(view), e.js.realm())
            || !d->stream)
        return web_idl::detail::create_rejected_promise<detail::readable_stream_read_result_t>(v8::Exception::TypeError());

    auto promise = ext::promise<detail::readable_stream_read_result_t>{};
    auto read_into_request = std::make_unique<detail::read_into_request_t>();
    read_into_request.chunk_steps = [&promise](detail::chunk_t* chunk) {promise.set_value({{"value", chunk}, {"done", false}});};
    read_into_request.close_steps = [&promise](detail::chunk_t* chunk) {promise.set_value({{"value", chunk}, {"done", true}});};
    read_into_request.error_steps = [&promise](const detail::error_t& error) {promise.set_exception(error);};

    detail::readable_stream_byob_reader_read(this, view, std::move(view), std::move(read_into_request));
    return promise;
}


auto streams::readable::readable_stream_byob_reader::release_lock()
        -> void
{
    return_if (!s_stream);
    detail::readable_stream_byob_reader_release(this);
}
