#include "readable_abstract_operations_internals.hpp"

#include "ext/assertion.hpp"

#include "streams/detail/miscellaneous_internals.hpp"
#include "streams/readable/readable_byte_stream_controller.hpp"
#include "streams/readable/readable_stream.hpp"
#include "streams/readable/readable_stream_private.hpp"
#include "streams/readable/readable_stream_byob_reader.hpp"
#include "streams/readable/readable_stream_byob_reader_private.hpp"
#include "streams/readable/readable_stream_default_controller.hpp"
#include "streams/readable/readable_stream_default_controller_private.hpp"
#include "streams/readable/readable_stream_default_reader.hpp"
#include "streams/readable/readable_stream_default_reader_private.hpp"


// Make these 2 the same method with a template for the desired type
auto streams::detail::acquire_readable_stream_byob_reader(
        readable::readable_stream* stream)
        -> std::unique_ptr<readable::readable_stream_byob_reader>
{
    auto reader = std::make_unique<readable::readable_stream_byob_reader>(stream);
    setup_readable_stream_byob_reader(reader.get(), stream);
    return reader;
}


auto streams::detail::acquire_readable_stream_default_reader(
        readable::readable_stream* stream)
        -> std::unique_ptr<readable::readable_stream_default_reader>
{
    auto reader = std::make_unique<readable::readable_stream_default_reader>();
    setup_readable_stream_default_reader(reader.get(), stream);
    return reader;
}


auto streams::detail::create_readable_stream(
        underlying_source_start_callback_t&& start_algorithm,
        underlying_source_pull_callback_t&& pull_algorithm,
        underlying_source_cancel_callback_t&& cancel_algorithm,
        ext::number<int> high_water_mark,
        size_algorithm_t&& size_algorithm)
        -> std::unique_ptr<readable::readable_stream>
{
    ASSERT (is_non_negative_number(high_water_mark));

    auto stream = std::make_unique<readable::readable_stream>();
    auto controller = std::make_unique<readable::readable_stream_default_controller>();
    initialize_readable_stream(stream.get());
    setup_readable_stream_default_controller(
            stream.get(), controller.get(),
            std::move(start_algorithm), std::move(pull_algorithm), std::move(cancel_algorithm),
            high_water_mark, std::move(size_algorithm));

    return stream;
}


auto streams::detail::create_readable_byte_stream(
        underlying_source_start_callback_t&& start_algorithm,
        underlying_source_pull_callback_t&& pull_algorithm,
        underlying_source_cancel_callback_t&& cancel_algorithm)
        -> std::unique_ptr<readable::readable_stream>
{
    auto stream = std::make_unique<readable::readable_stream>();
    auto controller = std::make_unique<readable::readable_byte_stream_controller>();
    initialize_readable_stream(stream.get());
    setup_readable_byte_stream_controller(
            stream.get(), controller.get(),
            std::move(start_algorithm), std::move(pull_algorithm), std::move(cancel_algorithm),
            0, ext::nullopt);

    return stream;
}


auto streams::detail::initialize_readable_stream(
        readable::readable_stream* stream)
        -> void
{
    stream->d_func()->state = readable_stream_state_t::READABLE;
    stream->d_func()->reader = nullptr;
    stream->d_func()->error = ext::any{nullptr};
    stream->d_func()->disturbed = false;
}


auto streams::detail::is_readable_stream_locked(
        const readable::readable_stream* stream)
        -> ext::boolean
{
    return stream->d_func()->reader.get() != nullptr;
}


auto streams::detail::readable_stream_pipe_to(
        readable::readable_stream* source,
        writable::writable_stream* destination,
        ext::boolean prevent_close,
        ext::boolean prevent_sbort,
        ext::boolean prevent_cancel,
        dom::abort::abort_signal* signal)
        -> ext::promise<void>
{
    ASSERT (!is_readable_stream_locked(source));
    ASSERT (!is_writable_stream_locked(destination));
}
