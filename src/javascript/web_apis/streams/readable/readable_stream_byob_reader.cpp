#include "readable_stream_byob_reader.hpp"

#include "dom/detail/exception_internals.hpp"


streams::readable::readable_stream_byob_reader::readable_stream_byob_reader(
        streams::readable::readable_stream* stream)
{
    detail::set_up_readable_stream_byob_reader(this, stream);
}


auto streams::readable::readable_stream_byob_reader::read(
        v8::Local<v8::ArrayBufferView> view)
        -> std::promise<ext::map<ext::string, ext::any>>
{
    if (view->ByteLength() == 0 || view->Buffer()->ByteLength() == 0 || !view->HasBuffer() || !s_stream)
    {
        std::promise<ext::map<ext::string, ext::any>> promise;
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    std::promise<ext::map<ext::string, ext::any>> promise;
    detail::read_into_request_t read_into_request
    {
        .chunk_steps = [&promise](detail::chunk_t* chunk) {promise.set_value({{"value", chunk}, {"done", false}});},
        .close_steps = [&promise](detail::chunk_t* chunk) {promise.set_value({{"value", chunk}, {"done", true}});},
        .error_steps = [&promise](const detail::error_t& error) {promise.set_exception(error);}
    };

    detail::readable_stream_byob_reader_read(this, view, std::move(read_into_request));
    return promise;
}


auto streams::readable::readable_stream_byob_reader::release_lock()
        -> void
{
    return_if (!s_stream);
    detail::readable_stream_byob_reader_release(this);
}
