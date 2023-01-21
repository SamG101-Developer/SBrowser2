module;
#include "ext/macros.hpp"
#include <swl/variant.hpp>
#include <function2/function2.hpp>


export module apis.fetch.types;

import apis.file_api.types;
import apis.html.types;
import apis.hr_time.types;
import apis.streams.types;
import apis.url.types;
import apis.xhr.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_MIXINS(fetch)
{
    class body;
}


DEFINE_FWD_DECL_NAMESPACE(fetch)
{
    class headers;
    class request;
    class response;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(fetch)
{
    // Header related
    enum class header_value_object_t {DICT, LIST, ITEM};
    enum class header_guard_t {IMMUTABLE, REQUEST, REQUEST_NO_CORS, RESPONSE, NONE};
    enum class method_t {GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE};

    using header_name_t = ext::u8string;
    using header_value_t = ext::u8string;
    using header_t = ext::pair<header_name_t, header_value_t>;

    using header_names_t = ext::vector<header_name_t>;
    using header_values_t = ext::vector<header_value_t>;
    using headers_t = ext::vector<header_t>;

    using request_info_t = ext::variant<std::unique_ptr<request>, ext::string>;
    using status_t = ext::number<int>;

    // Body related
    struct body_t;

    using xml_http_request_body_init_t = ext::variant<ext::variant_monostate_t , file_api::blob*, v8::ArrayBuffer, xhr::form_data*, ext::string>;
    using body_init_t = ext::extend_variant_t<xml_http_request_body_init_t, streams::readable_stream*>;
    using body_with_type_t = ext::tuple<std::unique_ptr<body_t>, header_value_t>;

    // Connection related
    struct connection_t;
    struct cache_entry_t;
    struct connection_timing_info_t;

    enum class new_connection_setting_t {NO, YES, YES_AND_DEDICATED};

    using network_partition_key_t = ext::pair<ext::string, ext::string>; // TODO : ?
    using connection_pool_t = ext::vector<connection_t*>;
    using proxy_t = ext::string;

    // Fetch related
    struct fetch_controller_t;
    struct fetch_timing_info_t;
    struct fetch_params_t;
    struct fetch_record_t;
    struct fetch_group_t;

    // Authentication related
    using authentication_entry_t = ext::tuple<ext::string, ext::string, v8::Local<v8::Context>>;
    using proxy_authentication_entry_t = authentication_entry_t;

    // Request related
    struct request_t;

    enum class deferred_window_t {CLIENT, NO_WINDOW};
    enum class request_initiation_t {DOWNLOAD, IMAGESET, MANIFEST, PREFETCH, PRERENDER, XSLT, _};
    enum class request_initiator_t {_, AUDIO, BEACON, BODY, CSS, EARLY_HINT, EMBED, FETCH, FONT, FRAME, IFRAME, IMAGE, IMG, INPUT, LINK, OBJECT, PING, SCRIPT, TRACK, VIDEO, XMLHTTPREQUEST, OTHER};
    enum class request_destination_t {_, AUDIO, AUDIOWORLET, DOCUMENT, MEBED, FONT, FRAME, IFRAME, IMAGE, MANIFEST, OBJECT, PAINTWORKLET, REPORT, SCRIPT, SHAREDWORKER, STYLE, TRACK, VIDEO, WORKER, XSLT, /* -- INNER -> */ SERVICEWORKER, WEBIDENTITY};
    enum class request_mode_t {_, SAME_ORIGIN, NO_CORS, CORS, /* -- INNER -> */ NAVIGATE, WEBSOCKET, ANONYMOUS};
    enum class request_credentials_t {OMIT, SAME_ORIGIN, INCLUDE};
    enum class request_cache_t {DEFAULT, NO_STORE, RELOAD, NO_CACHE, FORCE_CACHE, ONLY_IF_CACHED};
    enum class request_duplex_t {HALF};
    enum class request_redirect_t {FOLLOW, ERROR, MANUAL};

    using window_t = ext::variant<ext::variant_monostate_t, deferred_window_t, v8::Local<v8::Object>>;
    using request_init_t = ext::map<ext::string, ext::any>;
    using task_destination_t = ext::variant<html::detail::task_queue_t, v8::Local<v8::Object>>;

    // Response related
    struct response_t;
    struct response_body_info_t;

    enum class response_type_t {BASIC, CORS, DEFAULT, ERROR, OPAQUE, OPAQUE_REDIRECT};
    enum class response_cache_t {LOCAL, VALIDATED};
    enum class preload_response_t {PENDING};
    enum class policy_container_t {CLIENT};
    enum class fetch_controller_state_t {ONGOING, TERMINATED, ABORTED};
    enum class service_workers_mode_t {ALL, NONE};
    enum class referrer_t {NO_REFERRER, CLIENT};
    enum class parser_metadata_t  {PARSER_INSERTED, NOT_PARSER_INSERTED};
    enum class response_tainting_t {BASIC, CORS, OPAQUE};

    using response_init_t = ext::map<ext::string, ext::any>;
    using potential_destination_t = ext::variant<ext::string, request_destination_t>;
}


struct fetch::detail::fetch_params_t
{
    std::observer_ptr<request_t> request;

    ext::function<auto(int) -> void> process_request_body_chunk_length;
    ext::function<auto() -> void> process_request_end_of_body;
    ext::function<auto(response*) -> void> process_early_hints_response;
    ext::function<auto(response*) -> void> process_response;
    ext::function<auto(response*) -> void> process_response_end_of_body;
    ext::function<auto(response*) -> ext::u8string> process_response_consume_body;

    task_destination_t task_destination;
    ext::boolean cross_origin_isolated_capability = false;

    std::unique_ptr<fetch_controller_t> controller;
    std::unique_ptr<fetch_timing_info_t> timing_info;
    ext::variant<ext::variant_monostate_t, preload_response_t, std::unique_ptr<response_t>> preloaded_response_candidate;

    auto aborted() -> ext::boolean {return controller->state == fetch_controller_state_t::ABORTED;};
    auto termination() -> ext::boolean {return aborted() || controller->state == fetch_controller_state_t::TERMINATED;};
};


struct fetch::detail::fetch_controller_t
{
    fetch_controller_state_t state = fetch_controller_state_t::ONGOING;
    std::unique_ptr<fetch_timing_info_t> full_timing_info;
    ext::function<auto(v8::Local<v8::Object>) -> void> report_timing_steps;
    ext::function<auto() -> void> next_manual_redirect_steps;
    ext::map<ext::string, ext::any> serialized_abort_reason;
};


struct fetch::detail::fetch_timing_info_t
{
    hr_time::dom_high_res_time_stamp start_time = 0;
    hr_time::dom_high_res_time_stamp redirect_start_time = 0;
    hr_time::dom_high_res_time_stamp redirect_end_time = 0;
    hr_time::dom_high_res_time_stamp post_redirect_start_time = 0;
    hr_time::dom_high_res_time_stamp final_service_worker_start_time = 0;
    hr_time::dom_high_res_time_stamp final_network_request_start_time = 0;
    hr_time::dom_high_res_time_stamp final_network_response_start_time = 0;
    hr_time::dom_high_res_time_stamp end_time = 0;

    std::unique_ptr<connection_timing_info_t> final_connection_timing_info;
    ext::vector<ext::string> server_timing_headers{};
    ext::boolean render_blocking = false;
};


struct fetch::detail::response_body_info_t
{
    ext::number<int> encoded_size = 0;
    ext::number<int> decoded_size = 0;
};


struct fetch::detail::body_t
{
    body_t(ext::u8sting&& byte_sequence);

    std::unique_ptr<streams::readable_stream> stream;
    ext::variant<ext::u8string, std::unique_ptr<file_api::blob*>, std::unique_ptr<xhr::form_data>> source;
    ext::number<size_t> length;
};


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


struct fetch::detail::response_t
{
    response_t() = default;
    response_t(const response_t& response);

    response_type_t type = response_type_t::DEFAULT;
    ext::boolean aborted_flag;

    auto associated_url() -> url::detail::url_t;
    ext::vector<url::detail::url_t*> url_list;
    url::detail::url_t* const * url = url_list.end();

    ext::number<ushort> status;
    ext::u8string status_message;

    headers_t header_list;
    ext::variant<ext::u8string, std::shared_ptr<body_t>> body;

    response_cache_t cache_state;
    header_names_t cors_exposed_header_name_list;

    ext::boolean range_requested_flag;
    ext::boolean request_includes_credentials = true;
    ext::boolean timing_allow_passed_flag;

    std::shared_ptr<response_body_info_t> body_information;
    std::shared_ptr<service_workers::detail::service_worker_timing_info_t> service_worker_timing_information;
    ext::boolean has_cross_origin_redirects = false;

    //
    std::unique_ptr<response_t> internal_response;
};


struct fetch::detail::fetch_group_t
{
    ext::vector<std::unique_ptr<fetch_record_t>> fetch_records;
    std::observer_ptr<request_t> request;
    std::observer_ptr<fetch_controller_t> fetch_controller;

    ~fetch_group_t();
};


struct fetch::detail::connection_timing_info_t
{
    hr_time::dom_high_res_time_stamp domain_lookup_start_time = 0;
    hr_time::dom_high_res_time_stamp domain_lookup_end_time = 0;
    hr_time::dom_high_res_time_stamp connection_start_time = 0;
    hr_time::dom_high_res_time_stamp connection_end_time = 0;
    hr_time::dom_high_res_time_stamp secure_connection_start_time = 0;
    ext::u8string alpn_negotiated_protocol;
};


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
