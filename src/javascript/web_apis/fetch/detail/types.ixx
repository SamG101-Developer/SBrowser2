module;
#include "ext/macros.hpp"
#include <swl/variant.hpp>


export module apis.fetch.types;

import apis.url.types;
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
    struct body_t;
    struct connection_t;
    struct cache_entry_t;
    struct connection_timing_info_t;
    struct fetch_controller_t;
    struct fetch_timing_info_t;
    struct fetch_params_t;
    struct fetch_record_t;
    struct fetch_group_t;
    struct response_body_info_t;
    struct request_t;
    struct response_t;

    enum class new_connection_setting_t {NO, YES, YES_AND_DEDICATED};
    enum class header_value_object_t {DICT, LIST, ITEM};
    enum class header_guard_t {IMMUTABLE, REQUEST, REQUEST_NO_CORS, RESPONSE, NONE};
    enum class method_t {DELETE, GET, HEAD, OPTIONS, POST, PUT};

    enum class fetch_controller_state_t {ONGOING, TERMINATED, ABORTED};
    enum class service_workers_mode_t {ALL, NONE};
    enum class referrer_t {NO_REFERRER, CLIENT};
    enum class parser_metadata_t  {PARSER_INSERTED, NOT_PARSER_INSERTED};
    enum class response_tainting_t {BASIC, CORS, OPAQUE};

    enum class response_type_t {BASIC, CORS, DEFAULT, ERROR, OPAQUE, OPAQUE_REDIRECT};
    enum class response_cache_t {LOCAL, VALIDATED};

    enum class deferred_window_t {CLIENT, NO_WINDOW};
    enum class preload_response_t {PENDING};
    enum class policy_container_t {CLIENT};

    enum class request_initiation_t {DOWNLOAD, IMAGESET, MANIFEST, PREFETCH, PRERENDER, XSLT, _};
    enum class request_initiator_t {_, AUDIO, BEACON, BODY, CSS, EARLY_HINT, EMBED, FETCH, FONT, FRAME, IFRAME, IMAGE, IMG, INPUT, LINK, OBJECT, PING, SCRIPT, TRACK, VIDEO, XMLHTTPREQUEST, OTHER};
    enum class request_destination_t {_, AUDIO, AUDIOWORLET, DOCUMENT, MEBED, FONT, FRAME, IFRAME, IMAGE, MANIFEST, OBJECT, PAINTWORKLET, REPORT, SCRIPT, SHAREDWORKER, STYLE, TRACK, VIDEO, WORKER, XSLT, /* -- INNER -> */ SERVICEWORKER, WEBIDENTITY};
    enum class request_mode_t {_, SAME_ORIGIN, NO_CORS, CORS, /* -- INNER -> */ NAVIGATE, WEBSOCKET, ANONYMOUS};
    enum class request_credentials_t {OMIT, SAME_ORIGIN, INCLUDE};
    enum class request_cache_t {DEFAULT, NO_STORE, RELOAD, NO_CACHE, FORCE_CACHE, ONLY_IF_CACHED};
    enum class request_duplex_t {HALF};
    enum class request_redirect_t {FOLLOW, ERROR, MANUAL};

    // body related
    using xml_http_request_body_init_t = ext::variant<ext::variant_monostate_t , file_api::blob*, v8::ArrayBuffer, xhr::form_data*, ext::string>;
    using body_init_t = ext::extend_variant_t<xml_http_request_body_init_t, streams::readable::readable_stream*>;
    using body_with_type_t = ext::tuple<std::unique_ptr<body_t>, ext::string>;

    // connection related
    using network_partition_key_t = ext::pair<ext::string, ext::string>; // TODO : ?
    using connection_pool_t = ext::vector<connection_t*>;
    using proxy_t = ext::string;

    // header related
    using header_name_t = ext::u8string;
    using header_value_t = ext::u8string;
    using header_t = ext::pair<header_name_t, header_value_t>;

    using header_names_t = ext::vector<header_name_t>;
    using header_values_t = ext::vector<header_value_t>;
    using headers_t = ext::vector<header_t>;

    using request_info_t = ext::variant<std::unique_ptr<request>, ext::string>;

    // authentication related
    using authentication_entry_t = ext::tuple<ext::string, ext::string, v8::Local<v8::Context>>;
    using proxy_authentication_entry_t = authentication_entry_t;

    // request & response related
    using window_t = ext::variant<ext::variant_monostate_t, deferred_window_t, v8::Local<v8::Object>>;
    using request_init_t = ext::map<ext::string, ext::any>;
    using response_init_t = ext::map<ext::string, ext::any>;
    using task_desintation_t = ext::variant<html::task_queue_t, v8::Local<v8::Object>>;
}


struct fetch::detail::fetch_params_t
{
    std::observer_ptr<request_t> request;

    algorithm_t process_request_body_chunk_length;
    algorithm_t process_request_end_of_body;
    algorithm_t process_early_hints_response;
    algorithm_t process_response;
    algorithm_t process_response_end_of_body;
    algorithm_t process_response_consume_body;

    task_destination_t task_destination;
    ext::boolean cross_origin_isolated_capability = false;

    std::unique_ptr<fetch_controller_t> controller;
    std::unique_ptr<fetch_timing_info_t> timing_info;
    ext::variant<ext::variant_monostate_t, preload_response_t, std::unique_ptr<response_t>> preloaded_response_candidate;
};


struct fetch::detail::fetch_controller_t
{
    fetch_controller_state_t state = fetch_controller_state_t::ONGOING;
    std::unique_ptr<fetch_timing_info_t> full_timing_info;
    algorithm_t report_timing_steps;
    algorithm_t next_manual_redirect_steps;
    ext::map<ext::string, ext::any> serialized_abort_reason;
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
