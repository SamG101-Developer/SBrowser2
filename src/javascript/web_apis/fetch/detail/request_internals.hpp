#ifndef SBROWSER2_REQUEST_INTERNALS_HPP
#define SBROWSER2_REQUEST_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "fetch/_typedefs.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
#include INCLUDE_INNER_TYPES(url)

namespace fetch {class headers;}
namespace fetch {class request;}
namespace js::env {class env;}


namespace fetch::detail
{
    auto is_subresource_request(
            const request_t& request)
            -> ext::boolean;

    auto is_non_subresource_request(
            const request_t& request)
            -> ext::boolean;

    auto is_navigation_request(
            const request_t& request)
            -> ext::boolean;

    auto has_redirect_tainted_origin(
            const request_t& request)
            -> ext::boolean;

    auto serialize_request_origin(
            const request_t& request)
            -> ext::string;

    auto byte_serializing_request_origin(
            const request_t& request)
            -> ext::string;

    auto clone_request(
            const request_t& request)
            -> std::unique_ptr<request_t>;

    auto add_range_header_to_request(
            request_t& request,
            ext::number<int> first,
            ext::number<int> last = -1)
            -> void;

    auto check_if_cross_origin_embedder_policy_allows_credentials(
            const request_t& request)
            -> ext::boolean;

    auto create_request_object(
            std::unique_ptr<request_t>&& inner_request,
            header_guard_t header_guard)
            -> std::unique_ptr<request>;
}


struct fetch::detail::request_t
{
    request_t();
    request_t(const request_t&);
    ~request_t();

    method_t method = method_t::GET;
    std::shared_ptr<url::detail::url_t> url;

    ext::boolean local_urls_only_flag;
    ext::boolean unsafe_request_flag;
    headers_t header_list;
    ext::variant<ext::u8string, std::shared_ptr<body_t>> body;

    v8::Local<v8::Object> client;
    v8::Local<v8::Object> reserved_client;
    detail::window_t window;

    ext::string replaces_client;

    ext::boolean keep_alive = false;
    service_workers_mode_t service_workers_mode = service_workers_mode_t::ALL;
    request_initiator_t initiator_type;
    request_initiation_t initiator;
    request_destination_t destination;

    auto is_script_like() -> ext::boolean;

    ext::any priority;
    std::shared_ptr<html::detail::origin_t> origin = u"client";

    ext::variant<policy_container_t, std::shared_ptr<html::detail::policy_container_t>> policy_container;
    ext::variant<referrer_t, url::detail::url_t*> referrer = referrer_t::CLIENT;
    referrer_policy::detail::referrer_policy_t referrer_policy;

    request_mode_t mode = request_mode_t::NO_CORS;
    request_credentials_t credentials_mode = request_credentials_t::SAME_ORIGIN;
    request_cache_t cache_mode = request_cache_t::DEFAULT;
    request_redirect_t redirect_mode = request_redirect_t::FOLLOW;
    ext::boolean use_cors_preflight_flag;
    ext::boolean use_url_credentials_flag;

    ext::string integrity_metadata;
    ext::string cryptographic_nonce_metadata;
    parser_metadata_t parser_metadata;

    ext::boolean reload_navigation_flag;
    ext::boolean history_navigation_flag;
    ext::boolean user_activation;
    ext::boolean render_blocking;

    ext::vector<url::detail::url_t*> url_list;
    auto current_url() -> url::detail::url_t&;
    ext::number<int> redirect_count = 0;
    response_tainting_t response_tainting;
    ext::boolean prevent_no_cache_cache_control_header_modification_flag;
    ext::boolean done_flag;
    ext::boolean timing_allow_failed_flag;
};


#endif //SBROWSER2_REQUEST_INTERNALS_HPP
