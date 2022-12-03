#ifndef SBROWSER2_FETCH_TYPEDEFS_HPP
#define SBROWSER2_FETCH_TYPEDEFS_HPP


#include "ext/map.ixx"

#include "ext/tuple.ixx"
#include "ext/type_traits.ixx"
#include "ext/variant.ixx"

#include <v8-forward.h>
namespace fetch {class request;}
namespace file_api {class blob;}
namespace xhr {class form_data;}
namespace streams::readable {class readable_stream;}


namespace fetch::detail
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
}

#endif //SBROWSER2_FETCH_TYPEDEFS_HPP
