#include "readable_stream.hpp"

#include "ext/assertion.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/exception_internals.hpp"
#include "streams/_typedefs.hpp"


streams::readable::readable_stream::readable_stream()
{
    bind_get(locked);
}


streams::readable::readable_stream::readable_stream(
        ext::map<ext::string, ext::any>&& underlying_source,
        ext::map<ext::string, ext::any>&& strategy)
        : readable_stream{}
{
    using detail::readable_stream_type_t;
    detail::abstract_operation_internals::initialize_readable_stream(this);
    if (underlying_source.contains("type") && underlying_source.at("type").to<readable_stream_type_t>() != readable_stream_type_t::BYTES)
    {
        dom::detail::exception_internals::throw_v8_exception<V8_RANGE_ERROR>(
                [&strategy] {return strategy.try_emplace("size").second;},
                "The 'size' key of the dictionary can not be set if the underlying_type's 'type' is not bytes");

        auto high_water_mark = detail::abstract_operation_internals::extract_high_water(std::move(strategy), 0);
        detail::controller_internals::set_up_readable_byte_stream_controller_from_underlying_source(this, std::move(underlying_source), high_water_mark);
    }

    else
    {
        ASSERT(!underlying_source.contains("type"), "The 'type' item in the dictionary must be 'bytes'", underlying_source.at("type"));
        auto size_algorithm = detail::abstract_operation_internals::extract_size_algorithm(std::move(strategy));
        auto high_water_mark = detail::abstract_operation_internals::extract_high_water(std::move(strategy), 1);
        detail::controller_internals::set_up_readable_byte_stream_controller_from_underlying_source(this, std::move(underlying_source), high_water_mark, size_algorithm);
    }
}


template <typename T>
auto streams::readable::readable_stream::cancel(
        T&& reason)
        -> std::promise<void>
{
    if (detail::abstract_operation_internals::is_readable_stream_locked(this))
    {
        std::promise<void> promise;
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    return detail::abstract_operation_internals::readable_stream_cancel(this, std::forward<T>(reason));
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
    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return detail::is_readable_stream_locked(this);},
            "Can not pipe through a locked stream");

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [] {return detail::is_writeable_stream_locked(transform.at("writeable").to<writeable::writeable_stream*>());},
            "Can not pipe through a locked stream");

    auto* signal = options.try_emplace("signal", nullptr).first->second.to<dom::abort::abort_signal*>();
    auto promise = detail::abstract_operation_internals::readable_stream_pipe_to(
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
        -> std::promise<void>
{
    if (detail::abstract_operations_internals::is_readable_stream_locked(this))
    {
        std::promise<void> promise;
        promise.set_exception(); // TODO : JavaScript TypeError
        return promise;
    }

    if (detail::abstract_operations_internals::is_writeable_stream_locked(destination))
    {
        std::promise<void> promise;
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
        const -> ext::boolean
{
    return detail::abstract_operations_internals::is_readable_stream_locked(this);
}
