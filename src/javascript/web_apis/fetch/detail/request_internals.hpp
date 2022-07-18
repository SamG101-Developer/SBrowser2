#ifndef SBROWSER2_REQUEST_INTERNALS_HPP
#define SBROWSER2_REQUEST_INTERNALS_HPP


#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "url/url.hpp"
namespace fetch {class headers;}
namespace fetch {class request;}
namespace html::detail::policy_internals {struct policy_container;}

namespace fetch::detail::request_internals
{
    struct internal_request;
    enum class initiator_type_t {AUDIO, BEACON, BODY, CSS, EARLY_HINT, EMBED, FETCH, FONT, FRAME, IFRAME, IMAGE, IMG, INPUT, LINK, OBJECT, PING, SCRIPT, TRACK, VIDEO, XMLHTTPREQUEST, OTHER};
    enum class service_workers_mode_t {ALL, NONE};
    enum class initiator_t {DOWNLOAD, IMAGESET, MANIFEST, PREFETCH, PRERENDER, XSLT};
    enum class destination_t {AUDIO, AUDIOWORKLET, DOCUMENT, EMBED, FONT, FRAME, IFRAME, IMAGE, MANIFEST, OBJECT, PAINTWORKLET, REPORT, SCRIPT, SERVICEWORKER, SHAREDWORKER, STYLE, TRACK, VIDEO, WORKER, XSLT};
    enum class mode_t {SAME_ORIGIN, CORS, NO_CORS, NAVIGATE, WEBSOCKET, ANONYMOUS /* Should this be here -> in HTML spec */};
    enum class credentials_t {OMIT, SAME_ORIGIN, INCLUDE};
    enum class cache_t {DEFAULT, NO_STORE, RELOAD, NO_CACHE, FORCE_CACHE, ONLY_IF_CACHED};
    enum class redirect_t {FOLLOW, ERROR, MANUAL};
    enum class parser_metadata_t  {PARSER_INSERTED, NOT_PARSER_INSERTED};
    enum class response_tainting_t {BASIC, CORS, OPAQUE};


    auto is_subresource_request(
            internal_request& internal_request_object)
            -> ext::boolean;

    auto is_non_subresource_request(
            internal_request& internal_request_object)
            -> ext::boolean;

    auto is_navigation_request(
            internal_request& internal_request_object)
            -> ext::boolean;

    auto has_redirect_tainted_origin(
            internal_request& internal_request_object)
            -> ext::boolean;

    auto serialize_request_origin(
            internal_request& internal_request_object)
            -> ext::string;

    auto byte_serializing_request_origin(
            internal_request& internal_request_object)
            -> ext::string;

    auto clone_request(
            internal_request& internal_request_object)
            -> internal_request;

    auto add_range_header_to_request(
            internal_request& internal_request_object,
            ext::number_view<int> first,
            ext::number_view<int> last = -1)
            -> void;

    auto check_if_cross_origin_embedder_policy_allows_credentials(
            internal_request& internal_request_object)
            -> ext::boolean;

    auto create_request_object(
            internal_request& internal_request_object,
            header_guard_t header_guard,
            v8::Local<v8::Context> realm)
            -> request;
}


struct fetch::detail::request_internals::internal_request
{
    ext::string method = "GET";
    url::url_object url;

    ext::boolean local_urls_only_flag;
    ext::boolean unsafe_request_flag;
    headers_t header_list;
    detail::body_internals::internal_body body;

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

    std::unique_ptr<html::detail::policy_internals::policy_container> policy_container;
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

    ext::vector<url::url_object> url_list;
    auto associated_url() -> url::url_object;
    ext::number<int> redirect_count = 0;
    response_tainting_t response_tainting;
    ext::boolean prevent_no_cache_cache_control_header_modification_flag;
    ext::boolean done_flag;
    ext::boolean timing_allow_failed_flag;
};


#endif //SBROWSER2_REQUEST_INTERNALS_HPP
