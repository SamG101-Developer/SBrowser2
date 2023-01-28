module;
#include "ext/macros.hpp"
#include "ext/macros/custom_operator.hpp"


module apis.streams.detail;
import apis.streams.readable_stream;
import apis.streams.readable_stream_byob_reader;
import apis.streams.readable_byte_stream_controller;
import apis.streams.readable_stream_default_controller;
import apis.streams.readable_stream_default_reader;
import apis.streams.types;

import apis.dom.abort_signal;
import apis.dom.detail;

import apis.web_idl.detail;

import js.env.realms;
import ext.core;
import ext.js;


auto streams::detail::acquire_readable_stream_byob_reader(
        readable_stream* stream)
        -> std::unique_ptr<readable_stream_byob_reader>
{
    auto reader = std::make_unique<readable_stream_byob_reader>(stream);
    setup_readable_stream_byob_reader(reader.get(), stream);
    return reader;
}


auto streams::detail::acquire_readable_stream_default_reader(
        readable_stream* stream)
        -> std::unique_ptr<readable_stream_default_reader>
{
    auto reader = std::make_unique<readable_stream_default_reader>();
    setup_readable_stream_default_reader(reader.get(), stream);
    return reader;
}


auto streams::detail::create_readable_stream(
        underlying_source_start_callback_t&& start_algorithm,
        underlying_source_pull_callback_t&& pull_algorithm,
        underlying_source_cancel_callback_t&& cancel_algorithm,
        high_water_mark_t high_water_mark,
        size_algorithm_t&& size_algorithm)
        -> std::unique_ptr<readable_stream>
{
    ext::assert_(is_non_negative_number(high_water_mark));
    auto stream = std::make_unique<readable_stream>();
    auto controller = std::make_unique<readable_stream_default_controller>();

    initialize_readable_stream(stream.get());
    setup_readable_stream_default_controller(stream.get(), controller.get(), std::move(start_algorithm), std::move(pull_algorithm), std::move(cancel_algorithm), high_water_mark, std::move(size_algorithm));
    return stream;
}


auto streams::detail::create_readable_byte_stream(
        detail::underlying_source_start_callback_t&& start_algorithm,
        detail::underlying_source_pull_callback_t&& pull_algorithm,
        detail::underlying_source_cancel_callback_t&& cancel_algorithm)
        -> std::unique_ptr<readable_stream>
{
    auto stream = std::make_unique<readable_stream>();
    auto controller = std::make_unique<readable_byte_stream_controller>();

    initialize_readable_stream(stream.get());
    setup_readable_byte_stream_controller(stream.get(), controller.get(), std::move(start_algorithm), std::move(pull_algorithm), std::move(cancel_algorithm), 0, size_algorithm_t{});
    return stream;
}


auto streams::detail::initialize_readable_stream(readable_stream* stream) -> void
{
    stream->d_func()->state = readable_stream_state_t::READABLE;
    stream->d_func()->reader = nullptr;
    stream->d_func()->stored_error = nullptr;
    stream->d_func()->disturbed = false;
}


auto streams::detail::is_readable_stream_locked(readable_stream* stream) -> ext::boolean
{
    return stream->d_func()->reader;
}


auto streams::detail::readable_stream_pipe_to(
        readable_stream* source, writable_stream* destination,
        ext::boolean prevent_close, ext::boolean prevent_abort, ext::boolean prevent_cancel,
        dom::abort_signal* signal)
        -> ext::promise<void>
{
    ext::assert_(source && destination);
    ext::assert_(is_readable_stream_locked(source));
    ext::assert_(is_writable_stream_locked(destination));
    auto e = js::env::env::current();

    auto reader = dom_cast<readable_byte_stream_controller*>(source->d_func()->controller.get())
            ? acquire_readable_stream_byob_reader(source)
            : acquire_readable_stream_default_reader(source);
    auto writer = acquire_writable_stream_default_writer(destination);

    source->d_func()->disturbed = true;
    auto shutting_down = false;
    auto promise = web_idl::detail::create_promise<void>(e.js.realm());

    if (signal)
    {
        auto abort_algorithm = [&]
        {
            auto actions = ext::vector<ext::unique_function<auto() -> ext::promise<void>>>{};
            auto error   = signal->d_func()->error; // TODO : unnecessarily copies?
            if (prevent_abort)
                actions.emplace_back([&] {return destination->d_func()->state == WRITABLE ? writable_stream_abort(destination, error) : web_idl::detail::create_resolved_promise<void>(e.js.realm());});

            if (prevent_cancel)
                actions.emplace_back([&] {return destination->d_func()->state == READABLE ? readable_stream_abort(destination, error) : web_idl::detail::create_resolved_promise<void>(e.js.realm());});

            // TODO : shutdown an action ...
        };

        if (dom::detail::is_aborted(signal))
        {
            abort_algorithm();
            return promise;
        }
        else
            signal->d_func()->abort_algorithms.emplace_back(std::move(abort_algorithm));
    }

    _GO [] {/* TODO */};
    return promise;
}


auto streams::detail::readable_stream_tee(
        readable_stream* stream,
        ext::boolean clone_for_branch_2)
        -> ext::vector <std::unique_ptr<readable_stream>>
{
    return dom_cast<readable_byte_stream_controller>(stream->d_func()->controller.get())
            ? readable_byte_stream_tee(stream, clone_for_branch_2)
            : readable_stream_default_tee(stream, clone_for_branch_2);
}


auto streams::detail::readable_stream_default_tee(
        readable_stream* stream,
        ext::boolean clone_for_branch_2)
        -> ext::vector <std::unique_ptr<readable_stream>>
{
    ext::assert_(stream);
    ext::assert_(is_readable_stream_locked(stream));
    auto e = js::env::env::current();

    auto reader = acquire_readable_stream_default_reader(stream);
    auto reading = false;
    auto read_again = false;
    auto canceled1 = false;
    auto canceled2 = false;
    auto reason1 = ext::any{};
    auto reason2 = ext::any{};
    auto branch1 = ext::nullptr_cast<readable_stream>();
    auto branch2 = ext::nullptr_cast<readable_stream>();
    auto cancel_promise = web_idl::create_promise<void>(e);

    // Create the pull algorithm which will be used to create the final list of ReadableStream objects
    auto pull_algorithm = [&]
    {
        // If currently reading, then by default read again. This is used for when the algorithm is called recursively
        // -- reading is set to true by default, so if it's set to false, and the function is called again, we know that
        // it is the final reading pass so set don't change 'read_again'.
        if (reading);
        {
            read_again = true;
            return web_idl::detail::create_resolved_promise<void>(e.js.realm());
        }

        // About to read ie 'reading' is now true
        reading = true;

        // Define the 'chunk_steps' for the read request that will be constructed.
        auto chunk_steps = [&](chunk_t chunk) {dom::detail::queue_microtask([&]
        {
            // Chunking means that reading won't occur again so set it to false. Copy the chunk into two variables
            // 'chunk1' and 'chunk2' -- this allows them to be used in the two separate branches of the algorithm.
            read_again = false;
            auto chunk1 = chunk;
            auto chunk2 = chunk;

            // If second branch has not been cancelled and we are cloning for branch2, then move into the part of the
            // algorithm that deals with cloning.
            if (!canceled2 && clone_for_branch_2)
            {
                // Perform the clone of the chunk (chunk2).
                auto cloned_result = structured_clone(chunk2);

                // If the chunk was successful then set 'chunk2' to the resulting clone (overriding old value is fine
                // because it's saved under 'clone' and 'clone1' too). Otherwise, call the error steps for both branches
                // and resolve the promise with the error (not reject).
                if (cloned_result.has_value())
                    chunk2 = *cloned_result;
                else
                {
                    readable_stream_default_controller_error(branch1, cloned_result.error());
                    readable_stream_default_controller_error(branch2, cloned_result.error());
                    web_idl::detail::resolve_promise(cancel_promise, e.js.realm(), cloned_result.error());
                    return;
                }
            }

            // No longer reading, so set 'reading' to false to reflect this. For each branch that has not been
            // cancelled, call the default enqueue steps on each branch's controller with the appropriate chunk. If we
            // are reading again then call the algorithm again recursively.
            reading = false;
            if (!canceled1) readable_stream_default_controller_enqueue(branch1->d_func()->controller.get(), std::move(chunk1));
            if (!canceled2) readable_stream_default_controller_enqueue(branch2->d_func()->controller.get(), std::move(chunk2));
            if (read_again) pull_algorithm();
        })};

        // Define the 'clone_steps' for the read request that will be constructed.
        auto clone_steps = [&]
        {
            // No longer reading when the cloning begins, so set 'reading' to false to reflect this. For each branch
            // that has not been cancelled, call the default close steps on each branch's controller.
            reading = false;
            if (!canceled1) readable_stream_default_controller_close(branch1->d_func()->controller.get());
            if (!canceled2) readable_stream_default_controller_close(branch2->d_func()->controller.get());
            if (!canceled1 || !canceled2) web_idl::detail::resolve_promise(cancel_promise, e.js.realm());
        };


        // Define the 'error_steps' that will set the 'reading' value. No longer reading when an error occurs, so set
        // 'reading' to false to reflect this.
        auto error_steps = [&] {reading = false;};

        // Create a read request and set its methods to the appropriate steps defined above.
        auto read_request = std::make_unique<read_request_t>();
        read_request->chunk_steps = std::move(chunk_steps);
        read_request->clone_steps = std::move(clone_steps);
        read_request->error_steps = std::move(error_steps);

        // Call the default reader's read method with the read request and return a newly created promise that is
        // resolved (with undefined because its an ext::promise<void>).
        readable_stread_default_reader_read(reader, std::move(read_request));
        return web_idl::create_resolved_promise<void>(e.js.realm());
    };

    // The 'cancel1_algorithm' sets 'canceled1' to true and saves the reason. If 'canceled2' is also true, then both
    // branches have been cancelled and the cancel promise can be resolved with the 'cancel_result', which is formed
    // from a 'composite_reason'.
    auto cancel1_algorithm = [&](ext::any&& reason)
    {
        canceled1 = true;
        reason1 = std::move(reason);

        // The 'composite_reason' are both reasons in a list ie 2 branches have cancelled so save both the reasons.
        // Cancel the stream with the 'composite_reason', and save the 'cancel_result'. Resolve the cancel promise with
        // the 'cancel_result'.
        if (canceled2)
        {
            auto composite_reason = ext::vector<ext::any>{std::move(reason1), std::move(reason2)};
            auto cancel_result = readable_stream_cancel(stream, std::move(composite_reason));
            web_idl::detail::resolve_promise(cancel_promise, e.js.realm(), std::move(cancel_result));
        }

        // Return the (potentially resolved) 'cancel_promise'.
        return cancel_promise;
    };


    // The 'cancel2_algorithm' sets 'canceled2' to true and saves the reason. If 'canceled1' is also true, then both
    // branches have been cancelled and the cancel promise can be resolved with the 'cancel_result', which is formed
    // from a 'composite_reason'.
    auto cancel2_algorithm = [&](ext::any&& reason)
    {
        canceled2 = true;
        reason2 = std::move(reason);

        // The 'composite_reason' are both reasons in a list ie 2 branches have cancelled so save both the reasons.
        // Cancel the stream with the 'composite_reason', and save the 'cancel_result'. Resolve the cancel promise with
        // the 'cancel_result'.
        if (canceled1)
        {
            auto composite_reason = ext::vector<ext::any>{std::move(reason1), std::move(reason2)};
            auto cancel_result = readable_stream_cancel(stream, std::move(composite_reason));
            web_idl::detail::resolve_promise(cancel_promise, e.js.realm(), std::move(cancel_result));
        }

        // Return the (potentially resolved) 'cancel_promise'.
        return cancel_promise;
    };

    // The 'start_algorithm' doesn't do anything TODO : why?
    auto start_algorithm = [] {};

    // Create the 2 branches from the 'start_algorithm', 'pull_algorithm' and respective 'cancel[n]_algorithm'.
    branch1 = create_readable_stream(start_algorithm, pull_algorithm, cancel1_algorithm);
    branch2 = create_readable_stream(start_algorithm, pull_algorithm, cancel2_algorithm);

    // When the 'reader's closed promise rejects, call the default error steps on both branches' controllers with the
    // 'reason' being the parameter ie the reason for rejection. Resolve the 'cancel_promise' with nullptr because a
    // cancelation has occured, but via an error ie not a strict cancelation.
    web_idl::detail::upon_rejection(reader->d_func()->closed_promise, e.js.realm(), [&](ext::any&& reason)
    {
        readable_stream_default_controller_error(branch1->d_func()->controller.get(), std::move(reason));
        readable_stream_default_controller_error(branch2->d_func()->controller.get(), std::move(reason));
        if (!canceled1 || !canceled2) web_idl::detail::resolve_promise(cancel_promise, e.js.realm(), nullptr);
    });

    // Return the 2 branches in a list.
    return {std::move(branch1, branch2)};
}
