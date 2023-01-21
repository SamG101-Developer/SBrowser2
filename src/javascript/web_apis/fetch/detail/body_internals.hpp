#pragma once
#ifndef SBROWSER2_BODY_INTERNALS_HPP
#define SBROWSER2_BODY_INTERNALS_HPP







#include <v8-object.h>
#include <v8-array-buffer.h>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
namespace fetch::mixins {class body;}
namespace streams::readable {class readable_stream_default_reader;}

auto cors_check(
        request_t& request,
        response_t& response)
-> ext::boolean;

auto tao_check(
        request_t& request,
        response_t& response)
-> ext::boolean;
namespace fetch::detail
{
    using algorithm_t = ext::function<void()>;





    template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>


    template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>


    template <ext::type_is<v8::Local<v8::Object>, html::detail::task_queue_t> T>


    auto fully_read_body_as_promise(
            body_t& body)
            -> ext::promise<ext::u8string>;



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




#endif //SBROWSER2_BODY_INTERNALS_HPP
