module;
#include "ext/macros.hpp"
#include <v8-exception.h>


module apis.streams.writable_stream;
import apis.streams.detail;
import apis.streams.types;

import apis.dom.detail;
import apis.dom.types;
import apis.web_idl.detail;

import ext.core;
import ext.js;


streams::writable_stream::writable_stream(
        detail::underlying_sink_t&& underlying_sink,
        detail::queueing_strategy_t&& strategy)
{
    using namespace v8_primitive_error_t;
    dom::detail::throw_v8_exception<V8_RANGE_ERR>(
            [&underlying_sink] {return underlying_sink.contains(u"type")},
            u8"Underlying sink cannot contain a 'type' option", e);

    detail::initialize_writable_stream(this);
    auto size_algorithm = detail::extract_size_algorithm(strategy);
    auto high_water_mark = detail::extract_high_water_mark(std::move(strategy), 1);
    detail::setup_writable_stream_default_controller_from_underlying_sink(
            this, std::move(underlying_sink),
            std::move(high_water_mark), std::move(size_algorithm));
}


auto streams::writable_stream::abort(ext::any&& reason) -> ext::promise<void>
{
    return_if (detail::is_writable_stream_locked(this)) web_idl::detail::create_rejected_promise<void>(v8::TypeError(u"WritableStream is locked"));
    return detail::writable_stream_abort(this, std::move(reason));
}


auto streams::writable_stream::close() -> ext::promise<void>
{
    return_if (detail::is_writable_stream_locked(this)) web_idl::detail::create_rejected_promise<void>(v8::TypeError(u"WritableStream is locked"));
    return_if (detail::writable_stream_close_queued_or_in_flight(this)) web_idl::detail::create_rejected_promise<void>(v8::TypeError(u"WritableStream is already queued or in flight")
    return detail::writable_stream_close(this);
}


auto streams::writable_stream::get_writer() -> std::unique_ptr<writable_stream_default_writer>
{
    return detail::acquire_writable_stream_default_writer(this);
}


auto streams::writable_stream::get_locked() const -> ext::boolean
{
    return detail::is_writable_stream_locked(this);
}
