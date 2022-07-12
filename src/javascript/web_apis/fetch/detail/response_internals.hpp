#ifndef SBROWSER2_RESPONSE_INTERNALS_HPP
#define SBROWSER2_RESPONSE_INTERNALS_HPP


#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
#include "../_typedefs.hpp"
namespace fetch {class response;}
namespace fetch::detail::http_internals {class fetch_params;}
namespace fetch::detail::http_internals {class response_body_info;}
namespace service_workers::detail::service_worker_internals {struct service_worker_timing;}

namespace fetch::detail::response_internals
{
    struct internal_response;
    
    auto serialize_response_url_for_reporting(
            internal_response& internal_response_object)
            -> ext::string;

    auto is_aborted_network_error(
            internal_response& internal_response_object)
            -> ext::boolean;

    auto is_network_error(
            internal_response& internal_response_object)
            -> ext::boolean;

    auto appropriate_network_error(
            http_internals::fetch_params& params)
            -> internal_response;

    auto basic_filtered_response(
            internal_response& internal_response_object)
            -> const internal_response;

    auto cors_filtered_response(
            internal_response& internal_response_object)
            -> const internal_response;

    auto opaque_filtered_response(
            internal_response& internal_response_object)
            -> const internal_response;

    auto opaque_redirect_filtered_response(
            internal_response& internal_response_object)
            -> const internal_response;

    auto clone_response(
            internal_response& internal_response_object)
            -> internal_response;

    auto is_fresh_response(
            internal_response& response_object)
            -> ext::boolean;

    auto is_stale_while_revalidate_response(
            internal_response& internal_response_object)
            -> ext::boolean;

    auto is_stale_response(
            internal_response& internal_response_object)
            -> ext::boolean;

    auto location_url(
            internal_response& internal_response_object)
            -> url::url_object;

    auto create_response(
            internal_response& internal_response_object,
            header_guard_t header_guard,
            v8::Local<v8::Context> realm)
            -> response;

    auto initialize_response(
            response& response_object,
            ext::string_any_map_view init,
            body_internals::internal_body& internal_body_object)
            -> void;
}


struct fetch::detail::response_internals::internal_response
{
    enum class type_t {BASIC, CORS, DEFAULT, ERROR, OPAQUE, OPAQUE_REDIRECT};
    enum class cache_t {LOCAL, VALIDATED};

    type_t type {type_t::DEFAULT};
    ext::boolean aborted_flag;

    ext::vector<url::url_object> url_list;
    auto associated_url() -> url::url_object;

    ext::number<int> status;
    ext::string status_message;

    header_t header_list;
    std::unique_ptr<detail::body_internals::internal_body> body;

    cache_t cache_state;
    header_names_t cors_exposed_header_name_list;

    ext::boolean range_requested_flag;
    ext::boolean request_includes_credentials = true;
    ext::boolean timing_allow_passed_flag;

    detail::http_internals::response_body_info& body_information;
    service_workers::detail::service_worker_internals::service_worker_timing& service_worker_timing_information;
};


#endif //SBROWSER2_RESPONSE_INTERNALS_HPP
