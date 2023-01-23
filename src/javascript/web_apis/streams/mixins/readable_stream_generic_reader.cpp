module;
#include "ext/macros.hpp"


module apis.streams.mixins.readable_stream_generic_reader;
import apis.dom.dom_exception;

import ext.core;
import ext.js;


auto streams::mixins::readable_stream_generic_reader::cancel(ext::any&& reason) -> ext::promise<void>
{
    ACCESS_PIMPL(readable_stream_generic_reader);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {return !d->stream;},
            u8"Can not cancel a reader whose owner (ReadableStream) is null");

    return detail::readable_stream_reader_generic_cancel(dom_cast<readable_stream*>(this), reason);
}


auto streams::mixins::readable_stream_generic_reader::get_closed() const -> ext::promise<void>
{
    ACCESS_PIMPL;
    return d->closed_promise;
}
