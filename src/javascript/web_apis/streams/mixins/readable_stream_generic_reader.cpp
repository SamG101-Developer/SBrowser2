#include "readable_stream_generic_reader.hpp"

#include "dom/detail/exception_internals.hpp"


streams::mixins::readable_stream_generic_reader::readable_stream_generic_reader()
{
    bind_get(closed);
}


template <typename T>
auto streams::mixins::readable_stream_generic_reader::cancel(
        T&& reason)
        -> std::promise<void>
{
    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !s_stream;},
            "Can not cancel a reader whose owner (ReadableStream) is null");

    return detail::abstract_operations::readbale_steam_reader_generic_cancel(this, std::forward<T>(reason))
}


auto streams::mixins::readable_stream_generic_reader::get_closed()
        const -> std::promise<void>
{
    return s_closed_promise;
}
