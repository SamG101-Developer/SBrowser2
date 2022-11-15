#include "readable_stream_generic_reader.hpp"
#include "readable_stream_generic_reader_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "streams/readable/readable_stream.hpp"
#include "streams/detail/readable_abstract_operations_internals.hpp"


auto streams::mixins::readable_stream_generic_reader::cancel(ext::any reason) -> ext::promise<void>
{
    ACCESS_PIMPL(readable_stream_generic_reader);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->stream;},
            u8"Can not cancel a reader whose owner (ReadableStream) is null");

    return detail::readable_stream_reader_generic_cancel(dom_cross_cast<readable::readable_stream*>(this), reason);
}


auto streams::mixins::readable_stream_generic_reader::get_closed() const -> const ext::promise<void>&
{
    ACCESS_PIMPL(const readable_stream_generic_reader);
    return d->closed_promise;
}
