#include "readable_stream_default_reader.hpp"
#include "readable_stream_default_reader_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "streams/detail/readable_abstract_operations_internals.hpp"


streams::readable::readable_stream_default_reader::readable_stream_default_reader(
        streams::readable::readable_stream* stream)
{
    detail::setup_readable_stream_default_reader(this, stream);
}


auto streams::readable::readable_stream_default_reader::read(
        ext::array_buffer&& view)
        -> ext::promise<detail::readable_stream_read_result_t>
{
    ACCESS_PIMPL(readable_stream_default_reader);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->stream;},
            u8"Can not read with a ReadableStreamDefaultReader if the [[stream]] slot is empty");

    auto promise = ext::promise<ext::map<ext::string, ext::any>>{};
    auto read_request = std::make_unique<detail::read_request_t>();
    {
        .chunk_steps = [&promise](detail::chunk_t* chunk) {promise.set_value({{u"value", chunk}, {u"done", false}});},
        .close_steps = [&promise]() {promise.set_value({{u"value", u""}, {u"done", true}});},
        .error_steps = [&promise](const detail::error_t& error) {promise.set_exception(error);}
    };

    detail::readable_stream_default_reader_read(this, std::move(read_request));
    return promise;
}


auto streams::readable::readable_stream_default_reader::release_lock() -> void
{
    ACCESS_PIMPL(readable_stream_default_reader);
    return_if (!d->stream);
    detail::readable_stream_default_reader_release(this);
}
