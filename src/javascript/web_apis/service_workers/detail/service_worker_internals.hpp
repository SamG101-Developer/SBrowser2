#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_SERVICE_WORKER_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_SERVICE_WORKER_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/queue.hpp"
#include "ext/set.hpp"

#include "ext/promise.hpp"
#include <v8-forward.h>

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(service_workers)
#include INCLUDE_INNER_TYPES(storage)
#include INCLUDE_INNER_TYPES(url)

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

    auto get_service_worker_registration(
            v8::Local<v8::Object> environment,
            const service_worker_registration_t& service_worker_registration)
            -> workers::service_worker_registration*;

    auto soft_update(
            const service_worker_registration_t& registration,
            ext::boolean force_bypass_cache = false)
            -> void;

    auto install(
            const job_t& job,
            const service_worker_t& worker,
            const service_worker_registration_t& registration)
            -> void;

    auto activate(
            const service_worker_registration_t& registration)
            -> void;

    auto try_activate(
            const service_worker_registration_t& registration)
            -> void;

    auto run_service_worker(
            const service_worker_t& worker,
            ext::boolean force_bypass_cache = false)
            -> void;

    auto terminate_service_worker(
            const service_worker_t& worker)
            -> void;

    auto handle_service_worker_client_unload(
            const service_worker_client_t& client)
            -> void;

    auto handle_user_agent_shutdown()
            -> void;

    auto update_service_Worker_extended_events_set(
            const service_worker_t& service_worker,
            dom::events::event* event)
            -> void;

    auto update_worker_state(
            const service_worker_state_t& service_worker,
            service_worker_state_t state)
            -> void;

    auto notify_controller_change(
            const service_worker_client_t& client)
            -> void;

    auto get_newest_worker(
            const service_worker_registration_t& registration)
            -> service_worker_t;

    auto service_worker_has_no_pending_events(
            const service_worker_registration_t& registration)
            -> ext::boolean;

    auto is_async_module(
            /* TODO */)
            -> ext::boolean;

    auto is_running(...) -> ext::boolean;

    auto is_stale(...) -> ext::boolean;

    auto is_unregistered(...) -> ext::boolean;

    auto origin(...) -> ext::string;
}


struct service_workers::detail::service_worker_timing_info_t
{
    hr_time::dom_high_res_time_stamp start_time;
    hr_time::dom_high_res_time_stamp fetch_event_dispatch_time;
};




#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_SERVICE_WORKER_INTERNALS_HPP
