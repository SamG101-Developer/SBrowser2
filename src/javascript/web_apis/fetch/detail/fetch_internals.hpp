#ifndef SBROWSER2_FETCH_INTERNALS_HPP
#define SBROWSER2_FETCH_INTERNALS_HPP


#include "ext/boolean.ixx"

#include "ext/number.ixx"
#include "ext/string.hpp"

#include "connection_internals.hpp"
#include "header_internals.hpp"
#include "http_internals.hpp"
#include "request_internals.hpp"
#include "response_internals.hpp"


namespace fetch::detail
{
    auto fetch(
            request_t& request,
            ext::function<void(ext::number<int>)>&& process_request_body_chunk_length = nullptr,
            ext::function<void()>&& process_request_end_of_body = nullptr,
            ext::function<void(response_t&)>&& process_early_hints_response = nullptr,
            ext::function<void(response_t&)>&& process_response = nullptr,
            ext::function<void(response_t&)>&& process_response_end_of_body = nullptr,
            ext::function<void(response_t&, ext::string_view)>&& process_response_consume_body = nullptr,
            ext::boolean  use_parallel_queue = false)
            -> std::unique_ptr<response_t>;

    auto main_fetch(
            fetch_params_t& fetch_params,
            ext::boolean recursive = false)
            -> std::unique_ptr<response_t>;

    auto fetch_response_handover(
            fetch_params_t& fetch_params,
            response_t& response)
            -> void;

    auto scheme_fetch(
            fetch_params_t& fetch_params)
            -> std::unique_ptr<response_t>;

    auto http_fetch(
            fetch_params_t& fetch_params,
            ext::boolean make_cors_preflight = false)
            -> std::unique_ptr<response_t>;

    auto http_redirect_fetch(
            fetch_params_t& fetch_params,
            response_t& response)
            -> std::unique_ptr<response_t>;

    auto http_navigate_redirect_fetch(
            request_t& request,
            response_t& response)
            -> std::unique_ptr<response_t>;

    auto http_network_or_cache_fetch(
            fetch_params_t& fetch_params,
            ext::boolean is_authentication_fetch = false,
            ext::boolean is_new_connection_fetch = false)
            -> std::unique_ptr<response_t>;

    auto http_network_fetch(
            fetch_params_t& fetch_params,
            ext::boolean include_credentials = false,
            ext::boolean force_new_connection = false)
            -> std::unique_ptr<response_t>;

    auto cors_preflight_request(
            request_t& request)
            -> std::unique_ptr<response_t>;

    auto create_a_new_cache_entry(
            request_t& request,
            ext::number<int> max_age,
            ext::string_view method,
            header_name_t header_name)
            -> std::unique_ptr<cache_entry_t>;

    auto cors_check(
            request_t& request,
            response_t& response)
            -> ext::boolean;

    auto tao_check(
            request_t& request,
            response_t& response)
            -> ext::boolean;
}


// TODO : WindowOrWorkerGlobalScope with a fetch(...) method https://fetch.spec.whatwg.org/#fetch-method


struct fetch::detail::cache_entry_t
{
    network_partition_key_t key;
    ext::string byte_serialized_origin;
    std::unique_ptr<url::detail::url_t> url;
    ext::number<int> mag_age;
    ext::boolean credentials;
    ext::string method;
    header_name_t header_name;
};

#endif //SBROWSER2_FETCH_INTERNALS_HPP
