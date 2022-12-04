#pragma once
#ifndef SBROWSER2_BODY_INTERNALS_HPP
#define SBROWSER2_BODY_INTERNALS_HPP







#include <v8-object.h>
#include <v8-array-buffer.h>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
namespace fetch::mixins {class body;}
namespace streams::readable {class readable_stream_default_reader;}


namespace fetch::detail
{
    using algorithm_t = ext::function<void()>;

    auto clone_body(
            body_t& body)
            -> std::unique_ptr<body_t>;

    auto get_byte_sequence_as_body(
            ext::u8string_view byte_sequence)
            -> std::unique_ptr<body_t>;

    template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>
    auto incrementally_read_body(
            body_t& body,
            algorithm_t&& process_body_chunk,
            algorithm_t&& process_end_of_body,
            algorithm_t&& process_body_error,
            T&& task_destination)
            -> void;

    template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>
    auto incrementally_read_loop(
            streams::readable::readable_stream_default_reader* reader,
            T&& task_destination,
            algorithm_t&& process_body_chunk,
            algorithm_t&& process_end_of_body,
            algorithm_t&& process_body_error)
            -> void;

    template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>
    auto fully_read_body(
            body_t& body,
            algorithm_t&& process_body,
            algorithm_t&& process_body_error,
            T&& task_destination)
            -> void;

    auto fully_read_body_as_promise(
            body_t& body)
            -> ext::promise<ext::u8string>;

    auto handle_content_encodings(
            ext::string_view codings,
            ext::u8string_view bytes)
            -> ext::string; // TODO

    auto safely_extract_body(
            body_init_t&& object)
            -> detail::body_with_type_t;

    auto extract(
            body_init_t&& object,
            ext::boolean keepalive = false)
            -> detail::body_with_type_t;

    auto is_unusable(
            mixins::body* body)
            -> ext::boolean;

    auto package_data( // NOTE: different to file_api's package_data
            ext::string_view bytes,
            ext::string_view type,
            ext::string_view mime_type)
            -> ext::string;

    auto consume_body(
            mixins::body* body,
            ext::string_view type)
            -> auto; // TODO : not sure what the type should be -> std::future<...>?
}


struct fetch::detail::body_t
{
    std::unique_ptr<streams::readable::readable_stream> stream;
    ext::variant<ext::u8string, std::unique_ptr<file_api::blob*>, std::unique_ptr<xhr::form_data>> source;
    ext::number<size_t> length;
};


#endif //SBROWSER2_BODY_INTERNALS_HPP
