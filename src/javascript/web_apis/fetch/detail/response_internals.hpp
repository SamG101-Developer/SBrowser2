#ifndef SBROWSER2_RESPONSE_INTERNALS_HPP
#define SBROWSER2_RESPONSE_INTERNALS_HPP


#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(url)
namespace fetch {class response;}
namespace fetch::detail::http_internals {class fetch_params;}
namespace fetch::detail::http_internals {class response_body_info;}
namespace service_workers::detail::service_worker_internals {struct service_worker_timing;}

namespace fetch::detail
{
    auto serialize_response_url_for_reporting(
            response_t& internal_response_object)
            -> ext::string;

    auto is_aborted_network_error(
            response_t& internal_response_object)
            -> ext::boolean;

    auto is_network_error(
            response_t& internal_response_object)
            -> ext::boolean;

    auto appropriate_network_error(
            http_internals::fetch_params& params)
            -> response_t;

    auto basic_filtered_response(
            response_t& internal_response_object)
            -> const response_t;

    auto cors_filtered_response(
            response_t& internal_response_object)
            -> const response_t;

    auto opaque_filtered_response(
            response_t& internal_response_object)
            -> const response_t;

    auto opaque_redirect_filtered_response(
            response_t& internal_response_object)
            -> const response_t;

    auto clone_response(
            response_t& internal_response_object)
            -> response_t;

    auto is_fresh_response(
            response_t& response_object)
            -> ext::boolean;

    auto is_stale_while_revalidate_response(
            response_t& internal_response_object)
            -> ext::boolean;

    auto is_stale_response(
            response_t& internal_response_object)
            -> ext::boolean;

    auto location_url(
            response_t& internal_response_object)
            -> url::detail::url_t;

    auto create_response(
            response_t& internal_response_object,
            header_guard_t header_guard,
            v8::Local<v8::Context> realm)
            -> response;

    auto initialize_response(
            response& response_object,
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

    ext::vector<url::detail::url_t>& url_list;
    auto associated_url() -> url::detail::url_t;

    ext::number<int> status;
    ext::string status_message;

    headers_t& header_list;
    body_t& body;

    cache_t cache_state;
    header_names_t cors_exposed_header_name_list;

    ext::boolean range_requested_flag;
    ext::boolean request_includes_credentials = true;
    ext::boolean timing_allow_passed_flag;

    detail::http_internals::response_body_info& body_information;
    service_workers::detail::service_worker_internals::service_worker_timing& service_worker_timing_information;
};


#endif //SBROWSER2_RESPONSE_INTERNALS_HPP
