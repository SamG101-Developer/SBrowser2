module;
#include "ext/macros.hpp"


module apis.streams.readable_stream;
import apis.streams.writable_stream;
import apis.streams.detail;
import apis.streams.types;

import apis.dom.abort_signal;
import apis.dom.detail;
import apis.dom.types;

import apis.web_idl.detail;

import js.env.realms;
import ext.core;


streams::readable_stream::readable_stream(
        detail::underlying_source_t&& underlying_source,
        detail::queueing_strategy_t&& strategy)
{
    auto e = js::env::env::relevant(this);
    using enum v8_primitive_error_t;

    // Initializ the stream by calling the detail function which performs the initialization steps
    detail::initialize_readable_stream(this);

    // If the underlying source is a byte source, then throw as exception if "size" exists in the options (because
    // byte-size is automatically deduced. Calculate the high water mark from the detail function, and call another
    // detail function, which sets up this ReadableStream (already initialized).
    if (underlying_source[u"type"].to<detail::readable_stream_type_t>() == detail::readable_stream_type_t::BYTES)
    {
        dom::detail::throw_v8_exception<V8_RANGE_ERROR>([&strategy] {return strategy.contains(u"size");}, u8"Cannot have 'type' and 'size' set", e);
        auto high_water_mark = detail::extract_high_water_mark(strategy, 0);
        detail::setup_readable_byte_stream_controller_from_underlying_source(this, std::move(underlying_source), high_water_mark);
    }

    // If the underlying source is not a byte source, then assert "type" is not an option. Calculate the
    // 'high_water_mark' and create the 'size_algorithm' using the respective detail functions, and call another
    // detail function, which sets up this ReadableStream (already initialized), utilizing the 'size_algorithm'.
    else
    {
        ext::assert_(!underlying_source.contains(u"type"));
        auto size_algorithm = detail::extract_size_algorithm(strategy);
        auto high_water_mark = detail::extract_high_water_mark(strategy, 1);
        detail::setup_readable_stream_default_controller_from_underlying_source(this, std::move(underlying_source), high_water_mark, std::move(size_algorithm));
    }
}


streams::readable_stream::readable_stream(const readable_stream& other) // TODO
{
    auto e = js::env::env::relevant(this);
    using dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<DATA_CLONE_ERR>([&other] {return detail::is_readable_stream_locked(other);}, u8"Cannot transfer locked stream", e);

    auto port1 = std::make_unique<html::message_port>();
    auto port2 = std::make_unique<html::message_port>();
    html::detail::entangle_ports(*port1, *port2);

    auto writable = std::make_unique<writable_stream>();
    detail::setup_cross_realm_transform_writable(writable.get(), *port1);

    auto promise = detail::readable_stream_pipe_to(other, writable.get(), false, false, false);
    // TODO : promise.[[PromiseIsHandled]] = true

    auto c = js::env::env::current();
    d->port = html::detail::structured_serialize_with_transfer(*port2, {port2.get()});
    auto deserialized_record = html::detail::structed_deserialize_with_transform(d->port, c.js.realm());
    detail::setup_cross_realm_tranform_readable(&other, deserialized_record.d_func()->deserialized);
}


auto streams::readable_stream::cancel(
        ext::any&& reason)
        -> ext::promise<void>
{
    auto e = js::env::env::relevant(this);
    return !detail::is_readable_stream_locked(this)
            ? web_idl::detail::create_rejected_promise<void>(std::move(reason), e.js.realm())
            : detail::readable_stream_cancel(this, std::move(reason));
}


auto streams::readable_stream::get_reader(
        readable_stream_get_reader_options_t&& options)
        -> std::unique_ptr<mixins::readable_stream_generic_reader>
{
    return !options.contains(u"mode")
            ? detail::acquire_readable_stream_default_reader(this)
            : detail::acquire_readable_stream_byob_reader(this);

}


auto streams::readable_stream::pipe_through(
        readable_writable_pair_t&& transform,
        stream_pipe_options_t&& options)
        -> readable_stream*
{
    auto e = js::env::env::relevant(this);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>([this] {return detail::is_readable_stream_locked(this);}, u8"Can not pipe through a locked stream", e);
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>([&transform] {return detail::is_writable_stream_locked(transform[u"writable"].to<writable_stream*>());}, u8"Can not pipe through a locked stream", e);

    decltype(auto) signal = options[u"signal"].to<dom::abort_signal*>();
    auto promise = detail::readable_stream_pipe_to(
            this, transform[u"writable"].to<writable_stream*>(), transform[u"preventClose"].to<ext::boolean>(),
            transform[u"preventAbort"].to<ext::boolean>(), transform[u"preventCancel"].to<ext::boolean>(), signal);

    // TODO : promise.[[PromiseIsHandled]] = True
    return transform[u"readable"].to<readable_stream*>();
}


auto streams::readable_stream::pipe_to(
        writable_stream* destination,
        ext::map<ext::string, ext::any>&& options)
        -> ext::promise<void>
{
    auto e = js::env::env::relevant(this);
    
    if (detail::is_readable_stream_locked(this))
        return web_idl::detail::create_rejected_promise<void>(v8::Exception::TypeError(), e.js.realm());

    if (detail::is_writable_stream_locked(destination))
        return web_idl::detail::create_rejected_promise<void>(v8::Exception::TypeError(), e.js.realm());

    decltype(auto) signal = options[u"signal"].to<dom::abort_signal*>();
    return detail::readable_stream_pipe_to(
            this, destination, options[u"preventClose"].to<ext::boolean>(), options[u"preventAbort"].to<ext::boolean>(),
            options[u"preventCancel"].to<ext::boolean>(), signal);
}


auto streams::readable_stream::tee() -> ext::vector<std::unique_ptr<readable_stream>>
{
    return detail::readable_stream_tee(this, false);
}


auto streams::readable_stream::get_locked() const -> ext::boolean
{
    return detail::is_readable_stream_locked(this);
}
