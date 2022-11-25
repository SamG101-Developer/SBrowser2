#include "body_internals.hpp"

#include "interop/error_macros.hpp"
#include "javascript/environment/realms.hpp"

#include "fetch/detail/general_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"


auto fetch::detail::clone_body(body_t& body) -> std::unique_ptr<body_t>
{
    auto [out1, out2] = streams::detail::tee(body.stream.get());
    body.stream = std::move(out1);

    auto new_body = std::make_unique<body_t>();
    new_body->source = body.source; // TODO -> non-copyable
    new_body->stream = std::move(out2);
    new_body->length = body.length;
    return std::move(new_body);
}


auto fetch::detail::get_byte_sequence_as_body(ext::u8string_view byte_sequence) -> std::unique_ptr<body_t>
{
    using namespace ext::literals;
    auto body_with_type = safely_extract_body_with_type(byte_sequence);
    return body_with_type[0_tag];
}


template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>
auto fetch::detail::incrementally_read_body(
        body_t& body,
        algorithm_t&& process_body_chunk,
        algorithm_t&& process_end_of_body,
        algorithm_t&& process_body_error,
        T&& task_destination)
        -> void
{
    task_destination = task_destination.IsEmpty() ? start_new_parallel_queue() : task_destination;
    auto reader = streams::detail::get_reader(body.stream.get());
    incrementally_read_loop(
            streams::readable_stream_default_reader{}, std::forward<T>(task_destination),
            std::move(process_body_chunk), std::move(process_end_of_body), std::move(process_body_error));
}


template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>
auto fetch::detail::incrementally_read_loop(
        streams::readable::readable_stream_default_reader* reader,
        T&& task_destination,
        algorithm_t&& process_body_chunk,
        algorithm_t&& process_end_of_body,
        algorithm_t&& process_body_error)
        -> void
{
    auto continue_algorithm = [] {}; // TODO

    auto reader_request = streams::detail::read_request_t
            {
        .chunk_steps = BIND_FRONT(queue_fetch_task, std::move(continue_algorithm ), std::forward<T>(task_destination)),
        .close_steps = BIND_FRONT(queue_fetch_task, std::move(process_end_of_body), std::forward<T>(task_destination)),
        .error_steps = BIND_FRONT(queue_fetch_task, std::move(process_body_error ), std::forward<T>(task_destination))
            };

    streams::detail::read_chunk(reader, std::move(read_request));
}


template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>
auto fetch::detail::fully_read_body(
        body_t& body,
        algorithm_t&& process_body,
        algorithm_t&& process_body_error,
        T&& task_destination)
        -> void
{
    task_destination = task_destination.IsEmpty() ? start_new_parallel_queue() : task_destination;

    auto promise = fully_read_body_as_promise(body);
    auto fulfilled_steps =
            [task_destination = std::forward<T>(task_destination), process_body = std::move(process_body)]
            (ext::u8string byte_sequence) mutable {queue_fetch_task(BIND_FRONT(process_body, byte_sequence), task_destination);};

    auto rejection_steps =
            [task_destination = std::forward<T>(task_destination), process_body_error = std::move(process_body_error)]
            mutable {process_body_error(std::forward<T>(task_destination));};

    auto e = js::env::env::current(); // TODO : env
    web_idl::detail::react(promise, e.js.realm(), std::move(fulfilled_steps), std::move(rejection_steps));
}


auto fetch::detail::fully_read_body_as_promise(body_t& body) -> int
{
    JS_EXCEPTION_HANDLER;
    auto e = js::env::env::current(); // TODO : env
    auto reader = streams::detail::get_reader(body.stream.get());

    if (JS_EXCEPTION_HAS_THROWN)
        web_idl::detail::create_rejected_promise(JS_EXCEPTION, e.js.realm());
    return streams::detail::read_all_bytes(std::move(reader));
}
