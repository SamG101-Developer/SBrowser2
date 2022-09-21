#ifndef SBROWSER2_REQUEST_INTERNALS_HPP
#define SBROWSER2_REQUEST_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
#include INCLUDE_INNER_TYPES(url)

namespace fetch {class headers;}
namespace fetch {class request;}


namespace fetch::detail
{
    auto is_subresource_request(
            const request_t& internal_request_object)
            -> ext::boolean;

    auto is_non_subresource_request(
            const request_t& internal_request_object)
            -> ext::boolean;

    auto is_navigation_request(
            const request_t& internal_request_object)
            -> ext::boolean;

    auto has_redirect_tainted_origin(
            const request_t& internal_request_object)
            -> ext::boolean;

    auto serialize_request_origin(
            const request_t& internal_request_object)
            -> ext::string;

    auto byte_serializing_request_origin(
            const request_t& internal_request_object)
            -> ext::string;

    auto clone_request(
            const request_t& internal_request_object)
            -> request_t;

    auto add_range_header_to_request(
            const request_t& internal_request_object,
            ext::number<int> first,
            ext::number<int> last = -1)
            -> void;

    auto check_if_cross_origin_embedder_policy_allows_credentials(
            const request_t& internal_request_object)
            -> ext::boolean;

    auto create_request_object(
            const request_t& internal_request_object,
            header_guard_t header_guard,
            v8::Local<v8::Context> realm)
            -> request;
}


struct fetch::detail::request_t
{
    ext::string method = "GET";
    std::unique_ptr<url::detail::url_t> url;

    ext::boolean local_urls_only_flag;
    ext::boolean unsafe_request_flag;
    std::unique_ptr<headers_t> header_list;
    std::unique_ptr<body_t> body;

    v8::Local<v8::Object> client;
    v8::Local<v8::Object> reserved_client;
    v8::Local<v8::Object> window;

    ext::string replaces_client;

    ext::boolean keep_alive = false;
    initiator_type_t initiator_type;
    service_workers_mode_t service_workers_mode {service_workers_mode_t::ALL};
    initiator_t initiator;
    destination_t destination;

    auto is_script_like() -> ext::boolean;

    ext::any priority;
    ext::string origin {"client"};

    std::unique_ptr<html::detail::policy_container_t> policy_container;
    ext::variant<referrer_t, url::detail::url_t*> referrer = referrer_t::CLIENT;
    referrer_policy::detail::referrer_policy_t referrer_policy;
    mode_t mode {mode_t::NO_CORS};
    ext::boolean use_cors_preflight_flag;

    credentials_t credentials_mode = credentials_t::SAME_ORIGIN;
    ext::boolean use_url_credentials_flag;

    cache_t cache_mode = cache_t::DEFAULT;
    redirect_t redirect_mode {redirect_t::FOLLOW};

    ext::string integrity_metadata;
    ext::string cryptographic_nonce_metadata;
    parser_metadata_t parser_metadata;

    ext::boolean reload_navigation_flag;
    ext::boolean history_navigation_flag;
    ext::boolean user_activation;
    ext::boolean render_blocking;

    ext::vector<url::detail::url_t> url_list;
    auto associated_url() -> url::detail::url_t;
    ext::number<int> redirect_count = 0;
    response_tainting_t response_tainting;
    ext::boolean prevent_no_cache_cache_control_header_modification_flag;
    ext::boolean done_flag;
    ext::boolean timing_allow_failed_flag;
};


#endif //SBROWSER2_REQUEST_INTERNALS_HPP
