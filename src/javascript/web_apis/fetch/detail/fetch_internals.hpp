#ifndef SBROWSER2_FETCH_INTERNALS_HPP
#define SBROWSER2_FETCH_INTERNALS_HPP


#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"

#include "connection_internals.hpp"
#include "header_internals.hpp"
#include "http_internals.hpp"
#include "request_internals.hpp"
#include "response_internals.hpp"


namespace fetch::detail
{
    auto fetch(
            request_internals::internal_request& request_object,
            ext::function<void(ext::number<int>)>&& process_request_body_chunk_length,
            ext::function<void()>&& process_request_end_of_body = nullptr,
            ext::function<void(response_internals::internal_response&)>&& process_early_hints_response = nullptr,
            ext::function<void(response_internals::internal_response&)>&& process_response = nullptr,
            ext::function<void(response_internals::internal_response&)>&& process_response_end_of_body = nullptr,
            ext::function<void(response_internals::internal_response&, ext::string_view)>&& process_response_consume_body = nullptr,
            const ext::boolean& use_parallel_queue = false)
            -> http_internals::fetch_controller;

    auto main_fetch(
            http_internals::fetch_params& fetch_params_object,
            ext::boolean&& recursive = false)
            -> response_internals::internal_response;

    auto fetch_response_handover(
            http_internals::fetch_params& fetch_params_object,
            response_internals::internal_response& response_object)
            -> void;

    auto scheme_fetch(
            http_internals::fetch_params& fetch_params_object)
            -> response_internals::internal_response;

    auto http_fetch(
            http_internals::fetch_params& fetch_params_object,
            ext::boolean&& make_cors_preflight = false)
            -> response_internals::internal_response;

    auto http_redirect_fetch(
            http_internals::fetch_params& fetch_params_object,
            response_internals::internal_response& response_object)
            -> response_internals::internal_response;

    auto http_navigate_redirect_fetch(
            request_internals::internal_request& request_object,
            response_internals::internal_response& response_object)
            -> response_internals::internal_response;

    auto http_network_or_cache_fetch(
            http_internals::fetch_params& fetch_params_object,
            ext::boolean&& is_authentication_fetch = false,
            ext::boolean&& is_new_connection_fetch = false)
            -> response_internals::internal_response;

    auto http_network_fetch(
            http_internals::fetch_params& fetch_params_object,
            ext::boolean&& include_credentials = false,
            ext::boolean&& force_new_connection = false)
            -> response_internals::internal_response;

    auto cors_preflight_request(
            request_internals::internal_request& request_object)
            -> response_internals::internal_response;

    auto create_a_new_cache_entry(
            request_internals::internal_request& request_object,
            const ext::number<int>& max_age,
            ext::string_view method,
            header_name_t header_name)
            -> cache_entry;

    auto cors_check(
            request_internals::internal_request& request_object,
            response_internals::internal_response& response_object)
            -> ext::boolean;

    auto tao_check(
            request_internals::internal_request& request_object,
            response_internals::internal_response& response_object)
            -> ext::boolean;
}


// TODO : WindowOrWorkerGlobalScope with a fetch(...) method https://fetch.spec.whatwg.org/#fetch-method


struct fetch::detail::cache_entry_t
{
    network_partition_key_t key;
    ext::string byte_serialized_origin;
    url::url_object url;
    ext::number<int> mag_age;
    ext::boolean credentials;
    ext::string method;
    header_name_t header_name;
};

#endif //SBROWSER2_FETCH_INTERNALS_HPP
