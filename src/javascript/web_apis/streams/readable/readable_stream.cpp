#include "readable_stream.hpp"

#include "ext/assertion.hpp"





#include "streams/_typedefs.hpp"
#include "streams/detail/queue_abstract_operations.hpp"
#include "streams/detail/readable_abstract_operations_internals.hpp"

#include "v8-exception.h"
#include "web_idl/detail/type_mapping_internals.hpp"


streams::readable::readable_stream::readable_stream(
        detail::underlying_source_t&& underlying_source,
        detail::queueing_strategy_t&& strategy)
{
    using enum v8_primitive_error_t;

    detail::initialize_readable_stream(this);
    if (underlying_source[u"type"].to<detail::readable_stream_type_t>() == detail::readable_stream_type_t::BYTES)
    {
        dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
                [&strategy] {return strategy.contains(u"size");},
                u8"The 'size' key of the dictionary can not be set if the underlying_type's 'type' is bytes");

        auto high_water_mark = detail::extract_high_water_mark(std::move(strategy), 0);
        detail::setup_readable_byte_stream_controller_from_underlying_source(this, std::move(underlying_source), high_water_mark);
    }

    else
    {
        ASSERT(!underlying_source.contains(u"type"));
        auto size_algorithm = detail::extract_size_algorithm(std::move(strategy));
        auto high_water_mark = detail::extract_high_water_mark(std::move(strategy), 1);
        detail::setup_readable_stream_default_controller_from_underlying_source(this, std::move(underlying_source), high_water_mark, std::move(size_algorithm));
    }
}


auto streams::readable::readable_stream::cancel(
        ext::any reason)
        -> ext::promise<void>
{
    auto e = js::env::env::relevant(this);
    return !detail::is_readable_stream_locked(this)
            ? web_idl::detail::create_rejected_promise<void>(reason, e.js.realm())
            : detail::readable_stream_cancel(this, reason);
}


auto streams::readable::readable_stream::get_reader(
        detail::readable_stream_get_reader_options_t&& options)
        -> std::unique_ptr<abstract_readable_stream_reader>
{
    return !options.contains(u"mode")
            ? detail::acquire_readable_stream_default_reader(this)
            : detail::acquire_readable_stream_byob_reader(this);

}


auto streams::readable::readable_stream::pipe_through(
        detail::readable_writable_pair_t&& transform,
        detail::stream_pipe_options_t&& options)
        -> readable_stream*
{
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return detail::is_readable_stream_locked(this);},
            u8"Can not pipe through a locked stream");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [] {return detail::is_writable_stream_locked(transform[u"writable"].to<writable::writable_stream*>());},
            u8"Can not pipe through a locked stream");

    decltype(auto) signal = options[u"signal"].to<dom::abort::abort_signal*>();
    auto promise = detail::readable_stream_pipe_to(
            this,
            transform[u"writable"].to<writable::writable_stream*>(),
            transform[u"preventClose"].to<ext::boolean>(),
            transform[u"preventAbort"].to<ext::boolean>(),
            transform[u"preventCancel"].to<ext::boolean>(),
            signal);

    // TODO : set internal slot in the promise object
    return transform[u"readable"].to<readable_stream*>();
}


auto streams::readable::readable_stream::pipe_to(
        writable::writable_stream* destination,
        ext::map<ext::string, ext::any>&& options)
        -> ext::promise<void>
{
    auto e = js::env::env::relevant(this);
    
    if (detail::is_readable_stream_locked(this))
        return web_idl::detail::create_rejected_promise<void>(v8::Exception::TypeError(), e.js.realm());

    if (detail::is_writable_stream_locked(destination))
        return web_idl::detail::create_rejected_promise<void>(v8::Exception::TypeError(), e.js.realm());

    decltype(auto) signal = options[u"signal"].to<dom::abort::abort_signal*>();
    return detail::readable_stream_pipe_to(
            this,
            destination,
            options[u"preventClose"].to<ext::boolean>(),
            options[u"preventAbort"].to<ext::boolean>(),
            options[u"preventCancel"].to<ext::boolean>(),
            signal);
}


auto streams::readable::readable_stream::tee() -> ext::vector<std::unique_ptr<readable_stream>>
{
    return detail::readable_stream_tee(this, false);
}


auto streams::readable::readable_stream::get_locked() const -> ext::boolean
{
    return detail::is_readable_stream_locked(this);
}
