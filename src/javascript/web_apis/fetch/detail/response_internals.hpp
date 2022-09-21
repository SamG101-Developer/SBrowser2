#ifndef SBROWSER2_RESPONSE_INTERNALS_HPP
#define SBROWSER2_RESPONSE_INTERNALS_HPP

#include <memory>

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(service_workers)

namespace fetch {class response;}


namespace fetch::detail
{
    auto serialize_response_url_for_reporting(
            const response_t& internal_response_object)
            -> ext::string;

    auto is_aborted_network_error(
            const response_t& internal_response_object)
            -> ext::boolean;

    auto is_network_error(
            const response_t& internal_response_object)
            -> ext::boolean;

    auto appropriate_network_error(
            const fetch_params_t& params)
            -> response_t;

    auto basic_filtered_response(
            const response_t& internal_response_object)
            -> const response_t;

    auto cors_filtered_response(
            const response_t& internal_response_object)
            -> const response_t;

    auto opaque_filtered_response(
            const response_t& internal_response_object)
            -> const response_t;

    auto opaque_redirect_filtered_response(
            const response_t& internal_response_object)
            -> const response_t;

    auto clone_response(
            const response_t& internal_response_object)
            -> response_t;

    auto is_fresh_response(
            const response_t& response_object)
            -> ext::boolean;

    auto is_stale_while_revalidate_response(
            const response_t& internal_response_object)
            -> ext::boolean;

    auto is_stale_response(
            const response_t& internal_response_object)
            -> ext::boolean;

    auto location_url(
            const response_t& internal_response_object)
            -> url::detail::url_t;

    auto create_response(
            const response_t& internal_response_object,
            header_guard_t header_guard,
            v8::Local<v8::Context> realm)
            -> response;

    auto initialize_response(
            const response& response_object,
            ext::map<ext::string, ext::any>&& init,
            body_t& internal_body_object)
            -> void;
}


struct fetch::detail::response_t
{
    enum class type_t {BASIC, CORS, DEFAULT, ERROR, OPAQUE, OPAQUE_REDIRECT};
    enum class cache_t {LOCAL, VALIDATED};

    type_t type {type_t::DEFAULT};
    ext::boolean aborted_flag;

    ext::vector<url::detail::url_t*> url_list;
    auto associated_url() -> url::detail::url_t;

    ext::number<int> status;
    ext::string status_message;

    std::unique_ptr<headers_t> header_list;
    std::unique_ptr<body_t> body;

    cache_t cache_state;
    header_names_t cors_exposed_header_name_list;

    ext::boolean range_requested_flag;
    ext::boolean request_includes_credentials = true;
    ext::boolean timing_allow_passed_flag;

    std::unique_ptr<response_body_info_t> body_information;
    std::unique_ptr<service_workers::detail::service_worker_timing_info_t> service_worker_timing_information;
};


#endif //SBROWSER2_RESPONSE_INTERNALS_HPP
