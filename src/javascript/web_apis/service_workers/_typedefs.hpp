#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS__TYPEDEFS_HPP

#include "ext/map.hpp"
#include "ext/string.hpp"
#include "url/url.hpp"
#include USE_INNER_TYPES(fetch)

namespace service_workers::detail
{
    struct service_worker_t;
    struct service_worker_registration_t;
    struct service_worker_timing_info_t;
    struct service_worker_client_t;

    enum class service_worker_state_t {PARSED, INSTALLING, INSTALLED, ACTIVATING, ACTIVATED, REDUNDANT};
    enum class service_worker_type_t {CLASSIC, MODULE};
    enum class update_via_cache_mode_t {IMPORTS, ALL, NONE};
    enum class service_worker_update_via_cache_t {IMPORTS, ALL, NONE};
    enum class client_type_t {WINDOW, WORKER, SHAREDWORKER, ALL};
    enum class frame_type_t {AUXILIARY, TOP_LEVEL, NESTED, NONE};

    using script_resource_map_t = ext::map<url::url_object, fetch::detail::response_t*>;
    using registration_options_t = ext::map<ext::string, ext::any>;
    using navigation_preload_state_t = ext::map<ext::string, ext::any>;
    using client_query_options_t = ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS__TYPEDEFS_HPP
