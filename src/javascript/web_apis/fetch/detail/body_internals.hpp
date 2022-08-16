#pragma once
#ifndef SBROWSER2_BODY_INTERNALS_HPP
#define SBROWSER2_BODY_INTERNALS_HPP

#include "ext/functional.hpp"
#include "ext/number.hpp"
#include "ext/pair.hpp"
#include "ext/string.hpp"

#include <v8-object.h>
#include <v8-array-buffer.h>
#include USE_INNER_TYPES(fetch)
namespace fetch::mixins {class body;}
namespace streams::readable {class readable_stream_default_reader;}

namespace fetch::detail
{
    using algorithm_t = ext::function<void()>;

    auto clone_body(
            internal_body& body_object)
            -> internal_body;

    auto incrementally_read_body(
            internal_body& body_object,
            algorithm_t&& process_body_chunk,
            algorithm_t&& process_end_of_body,
            algorithm_t&& process_body_error,
            v8::Local<v8::Object> task_destination)
            -> void;

    auto incrementally_read_loop(
            streams::readable::readable_stream_default_reader* reader,
            v8::Local<v8::Object> task_destination,
            algorithm_t&& process_body_chunk,
            algorithm_t&& process_end_of_body,
            algorithm_t&& process_body_error)
            -> void;

    auto fully_read_body(
            internal_body& body_object,
            algorithm_t&& process_body,
            algorithm_t&& process_body_error,
            v8::Local<v8::Object> task_destination)
            -> void;

    auto fully_read_body_as_promise(
            internal_body& body_object)
            -> void;

    auto safely_extract_body(
            body_init_t object)
            -> ext::pair<internal_body, ext::string>;

    auto extract(
            body_init_t object,
            const ext::boolean& keepalive = false)
            -> ext::pair<internal_body, ext::string>;

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
    streams::readable::readable_stream* stream;
    ext::string source;
    ext::number<size_t> length;
};


#endif //SBROWSER2_BODY_INTERNALS_HPP
