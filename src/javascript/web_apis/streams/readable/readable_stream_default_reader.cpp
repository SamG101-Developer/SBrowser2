#include "readable_stream_default_reader.hpp"

#include "dom/detail/exception_internals.hpp"


streams::readable::readable_stream_default_reader::readable_stream_default_reader(
        streams::readable::readable_stream* stream)
{
    detail::set_up_readable_stream_default_reader(this, stream);
}


auto streams::readable::readable_stream_default_reader::read(
        v8::Local<v8::ArrayBufferView> view)
        -> ext::promise<ext::map<ext::string, ext::any>>
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !s_stream;},
            "Can not read with a ReadableStreamDefaultReader if the [[stream]] slot is empty");

    ext::promise<ext::map<ext::string, ext::any>> promise;
    detail::read_request_t read_request
    {
        .chunk_steps = [&promise](detail::chunk_t* chunk) {promise.set_value({{"value", chunk}, {"done", false}});},
        .close_steps = [&promise]() {promise.set_value({{"value", ""}, {"done", true}});},
        .error_steps = [&promise](const detail::error_t& error) {promise.set_exception(error);}
    };

    detail::readable_stream_default_reader_read(this, std::move(read_request));
    return promise;
}


auto streams::readable::readable_stream_default_reader::release_lock()
        -> void
{
    return_if (!s_stream);
    detail::readable_stream_default_reader_release(this);
}
