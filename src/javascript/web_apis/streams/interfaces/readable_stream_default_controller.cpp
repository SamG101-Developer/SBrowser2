module;
#include "ext/macros.hpp"


module apis.streams.readable_stream_default_controller;
import apis.streams.detail;
import apis.streams.types;

import apis.dom.detail;
import apis.dom.types;

import js.env.realms;
import ext.core;


auto streams::readable_stream_default_controller::close() -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !detail::readable_stream_default_controller_can_close_or_enqueue(this);},
            u8"Readable stream unable to close", e);

    detail::readable_stream_default_controller_close(this);
}


auto streams::readable_stream_default_controller::enqueue(detail::chunk_t chunk) -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return !detail::readable_stream_default_controller_can_close_or_enqueue(this);},
            u8"Readable stream unable to close", e);

    detail::readable_stream_default_controller_enqueue(this, std::move(chunk));
}


auto streams::readable_stream_default_controller::error(ext::any&& error) -> void
{
    detail::readable_stream_default_controller_error(this, std::move(error));
}


auto streams::readable_stream_default_controller::get_desired_size() const -> ext::number<double>
{
    return detail::readable_stream_default_controller_get_desired_size(this);
}
