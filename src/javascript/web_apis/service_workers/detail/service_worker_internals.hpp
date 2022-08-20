#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_SERVICE_WORKER_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_SERVICE_WORKER_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/set.hpp"
#include "url/url.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(high_resolution_time)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(service_workers)
#include USE_INNER_TYPES(storage)

namespace service_workers::events {class extendable_event;}
namespace service_workers::workers {class service_worker;}
namespace service_workers::workers {class service_worker_global_scope;}
namespace service_workers::workers {class service_worker_registration;}
namespace service_workers::other {class navigation_preload_manager;}

namespace service_workers::detail
{
    auto is_window_client(
            service_worker_client_t* client)
            -> ext::boolean;

    auto is_dedicated_worker_client(
            service_worker_client_t* client)
            -> ext::boolean;

    auto is_shared_client(
            service_worker_client_t* client)
            -> ext::boolean;

    auto is_worker_client(
            service_worker_client_t* client)
            -> ext::boolean;

    auto get_service_worker_object(
            v8::Local<v8::Object> environment,
            const service_worker_t& service_worker)
            -> workers::service_worker*;

    auto get_the_service_worker_registration(
            v8::Local<v8::Object> environment,
            const service_worker_registration_t& service_worker_registration)
            -> workers::service_worker_registration*;
};


struct service_workers::detail::service_worker_t
{
    service_worker_state_t state = service_worker_state_t::PARSED;
    service_worker_type_t type = service_worker_type_t::CLASSIC;
    script_resource_map_t script_resource_map;
    service_worker_registration_t& containing_worker_registration;

    url::url_object script_url;
    html::detail::script_t script;
    html::detail::policy_container_t& policy_container;
    workers::service_worker_global_scope* global_object;

    ext::boolean has_even_been_evaluated_flag;
    ext::boolean skip_waiting_flag;
    ext::boolean classic_scripts_imported_flag;

    ext::set<url::url_object> used_scripts;
    ext::set<ext::string> events_types_to_handle;
    ext::set<events::extendable_event*> extended_events;

    ext::boolean start_status;

    auto running() -> ext::boolean;
};


struct service_workers::detail::service_worker_registration_t
{
    storage::detail::storage_key_t storage_key;
    url::url_object scope_url;
    service_worker_t* installing_worker;
    service_worker_t* waiting_worker;
    service_worker_t* active_worker;

    ext::number<int> last_registered_check_time;
    update_via_cache_mode_t update_via_cache_mode = update_via_cache_mode_t::IMPORTS;
    // TODO : task queues

    other::navigation_preload_manager* manager;
    ext::boolean navigation_preload_enabled_flag;
    ext::string preload_header_value = "true";

    auto stale() -> ext::boolean;
    auto unregistered() -> ext::boolean;
};


struct service_workers::detail::service_worker_timing_info_t
{
    high_resolution_time::detail::dom_high_res_time_stamp_t start_time;
    high_resolution_time::detail::dom_high_res_time_stamp_t fetch_event_dispatch_time;
};


struct service_workers::detail::service_worker_client_t
{
    ext::boolean discarded_flag;
    // TODO : environment discarding steps

    auto origin() -> ext::string;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_SERVICE_WORKER_INTERNALS_HPP
