#include "readable_abstract_operations_internals.hpp"

#include "ext/assertion.hpp"
#include "ext/casting.hpp"
#include "ext/hashing.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/abort/abort_signal_private.hpp"

#include "ext/tuple.hpp"
#include "streams/_typedefs.hpp"
#include "streams/detail/miscellaneous_internals.hpp"
#include "streams/detail/writable_abstract_operations.hpp"

#include "streams/readable/readable_byte_stream_controller.hpp"
#include "streams/readable/readable_stream.hpp"
#include "streams/readable/readable_stream_private.hpp"
#include "streams/readable/readable_stream_byob_reader.hpp"
#include "streams/readable/readable_stream_byob_reader_private.hpp"
#include "streams/readable/readable_stream_default_controller.hpp"
#include "streams/readable/readable_stream_default_controller_private.hpp"
#include "streams/readable/readable_stream_default_reader.hpp"
#include "streams/readable/readable_stream_default_reader_private.hpp"

#include "streams/writable/writable_stream.hpp"
#include "streams/writable/writable_stream_private.hpp"
#include "streams/writable/writable_stream_default_writer.hpp"
#include "streams/writable/writable_stream_default_writer_private.hpp"

#include "web_idl/detail/type_mapping_internals.hpp"


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
    stream->d_func()->stored_error = ext::any{nullptr};
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
        ext::boolean prevent_abort,
        ext::boolean prevent_cancel,
        dom::abort::abort_signal* signal)
        -> ext::promise<void>
{
    ASSERT (!is_readable_stream_locked(source));
    ASSERT (!is_writable_stream_locked(destination));
    using action_t = ext::function<ext::promise<void>()>;

    auto reader = dom_cast<readable::readable_byte_stream_controller*>(source->d_func()->controller.get())
            ? acquire_readable_stream_byob_reader(source)
            : acquire_readable_stream_default_reader(source);
    auto writer = acquire_writable_stream_default_writer(destination);

    source->d_func()->disturbed = true;
    auto shutting_down = ext::boolean::FALSE_();
    auto promise = ext::promise<void>{};
    auto e = js::env::env::current(); // TODO : which env

    auto shutdown = []<typename T>(ext::promise<T>& promise) {};
    auto shutdown_action = []<typename T>(ext::promise<T>& promise, action_t action) {};

    if (signal)
    {
        auto abort_algorithm =
                [prevent_abort, prevent_cancel, &e, &signal, &source, &destination, &shutdown_action]
                {
            auto error   = signal->d_func()->abort_reason;
            auto actions = ext::vector<action_t>{}; // TODO

            if (!prevent_abort) actions.emplace_back([&e, &destination, &error] {return destination.d_func()->state == writable_stream_state_t::WRITABLE
                    ? writable_stream_abort(destination, error)
                    : web_idl::detail::create_resolved_promise(e.js.realm());});

            if (!prevent_cancel) actions.emplace_back([&e, &source, &error] {return source.d_func()->state == readable_stream_state_t::READABLE
                    ? readable_stream_cancel(source, error)
                    : web_idl::detail::create_resolved_promise(e.js.realm());});

            shutdown_action(web_idl::detail::get_promise_for_waiting_for_all(actions, e.js.realm()), error);
                };

        if (signal->d_func()->aborted())
        {
            abort_algorithm();
            return promise;
        }

        signal.d_func()->abort_algorithms.emplace_back(std::move(abort_algorithm));
    }

    GO []
    {
        // TODO
    };

    // TODO
}


auto streams::detail::readable_stream_tee(
        readable::readable_stream* stream,
        ext::boolean clone_for_branch_2)
        -> ext::vector<std::unique_ptr<readable::readable_stream>>
{
    return dom_cast<readable::readable_byte_stream_controller*>(stream->d_func()->controller.get())
            ? readable_byte_stream_tee(stream)
            : readable_stream_default_tee(stream, clone_for_branch_2);
}


auto streams::detail::readable_byte_stream_tee(
        readable::readable_stream* stream)
        -> ext::vector<std::unique_ptr<readable::readable_stream>>
{
    auto reader = acquire_readable_stream_default_reader(stream);
    auto [reading, read_again, canceled1, canceled2] = ext::make_repeat_tuple<ext::boolean, 4>();
    auto [reason1, reason2, branch1, branch2]        = ext::make_repeat_tuple<ext::any, 4>();
    auto cancel_promise = ext::promise<void>();
}
