#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS__TYPEDEFS_HPP

#include "ext/map.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(storage)
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)

namespace fetch {class request;}
namespace fetch {class response;}

namespace service_workers::detail
{
    struct service_worker_t;
    struct service_worker_registration_t;
    struct service_worker_timing_info_t;
    struct service_worker_client_t;
    struct cache_batch_operation_t;
    struct job_t;

    enum class service_worker_state_t {PARSED, INSTALLING, INSTALLED, ACTIVATING, ACTIVATED, REDUNDANT};
    enum class service_worker_type_t {CLASSIC, MODULE};
    enum class update_via_cache_mode_t {IMPORTS, ALL, NONE};
    enum class service_worker_update_via_cache_t {IMPORTS, ALL, NONE};
    enum class client_type_t {WINDOW, WORKER, SHAREDWORKER, ALL};
    enum class frame_type_t {AUXILIARY, TOP_LEVEL, NESTED, NONE};
    enum class cache_batch_operation_type_t {DELETE, PUT};
    enum class job_type_t {REGISTER, UPDATE, UNREGISTER};
    enum class target_t {INSTALLING, WAITING, ACTIVE};

    using script_resource_map_t = ext::map<url::detail::url_t, fetch::detail::response_t*>;
    using registration_options_t = ext::map<ext::string, ext::any>;
    using navigation_preload_state_t = ext::map<ext::string, ext::any>;
    using client_query_options_t = ext::map<ext::string, ext::any>;
    using cache_query_options_t = ext::map<ext::string, ext::any>;
    using multi_cache_query_options_t = cache_query_options_t;
    using request_response_list_t = ext::vector<ext::pair<fetch::request*, fetch::response*>>;
    using name_to_cache_map_t = ext::map<ext::string, request_response_list_t*>;
    using registration_map = ext::map<ext::tuple<storage::detail::storage_key_t, ext::string>, service_worker_registration_t*>;
    using job_queue_t = ext::queue<job_t>;
    using scope_to_job_queue_map_t = ext::map<ext::string, job_queue_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS__TYPEDEFS_HPP
