#include "readable_stream.hpp"

#include "ext/assertion.hpp"

#include "dom/_typedefs.hpp"
#include "dom/abort/abort_signal.hpp"
#include "dom/detail/exception_internals.hpp"

#include "streams/_typedefs.hpp"
#include "streams/detail/queue_abstract_operations.hpp"
#include "streams/detail/readable_abstract_operations_internals.hpp"

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


auto streams::readable::readable_stream::cancel(ext::any reason) -> ext::promise<void>
{
    auto e = js::env::env::relevant(this);
    return !detail::is_readable_stream_locked(this)
            ? web_idl::detail::create_rejected_promise<void>(reason, e.js.realm())
            : detail::readable_stream_cancel(this, reason);
}


auto streams::readable::readable_stream::get_reader(
        ext::map<ext::string, ext::any>&& options)
        -> detail::readable_stream_reader_t
{
    return !options.contains("mode")
            ? detail::abstract_operations_internals::acquire_readable_stream_default_reader(this)
            : detail::abstract_operations_internals::acquire_readable_stream_byob_reader(this);

}


auto streams::readable::readable_stream::pipe_through(
        ext::map<ext::string, ext::any>&& transform,
        ext::map<ext::string, ext::any>&& options)
        -> readable_stream*
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return detail::is_readable_stream_locked(this);},
            "Can not pipe through a locked stream");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [] {return detail::is_writeable_stream_locked(transform.at("writeable").to<writeable::writeable_stream*>());},
            "Can not pipe through a locked stream");

    auto* signal = options.try_emplace("signal", nullptr).first->second.to<dom::abort::abort_signal*>();
    auto promise = detail::readable_stream_pipe_to(
            this,
            transform.try_emplace("writeable", false).first->second.to<ext::boolean>(),
            transform.try_emplace("preventClose", nullptr).first->second.to<writeable::writeable_stream*>(),
            transform.try_emplace("preventAbort", false).first->second.to<ext::boolean>(),
            transform.try_emplace("preventCancel", false).first->second.to<ext::boolean>(),
            signal);

    // TODO : set internal slot in the promise object
    return transform.at("readable").to<readable_stream*>;
}


auto streams::readable::readable_stream::pipe_to(
        writeable::writeable_stream* destination,
        ext::map<ext::string, ext::any>&& options)
        -> ext::promise<void>
{
    if (detail::abstract_operations_internals::is_readable_stream_locked(this))
    {
        ext::promise<void> promise;
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    if (detail::abstract_operations_internals::is_writeable_stream_locked(destination))
    {
        ext::promise<void> promise;
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    auto* signal = options.try_emplace("signal", nullptr).first->second.to<dom::abort::abort_signal*>();
    return detail::abstract_operations_internals::readable_stream_pipe_to(
            this,
            destination,
            options.try_emplace("preventClose", nullptr).first->second.to<writeable::writeable_stream*>(),
            options.try_emplace("preventAbort", false).first->second.to<ext::boolean>(),
            options.try_emplace("preventCancel", false).first->second.to<ext::boolean>()
            signal);
}


auto streams::readable::readable_stream::tee()
        -> ext::vector<readable_stream*>
{
    return detail::abstract_operations_internals::readable_stream_tee(this, false);
}


auto streams::readable::readable_stream::get_locked()
        const -> decltype(this->locked)::value_t
{
    return detail::abstract_operations_internals::is_readable_stream_locked(this);
}
