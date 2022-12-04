#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_JOB_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_JOB_INTERNALS_HPP


#include "ext/expected.ixx"
#include "ext/promise.ixx"
#include "service_workers/clients/client.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(storage)
#include INCLUDE_INNER_TYPES(service_workers)
#include INCLUDE_INNER_TYPES(url)


namespace service_workers::detail
{

    auto is_bad_import_script_response(
            const fetch::detail::response_t&)
            -> ext::boolean;

    auto create_job(
            job_type_t job_type,
            storage::detail::storage_key_t&& storage_key,
            url::detail::url_t&& scope_url,
            url::detail::url_t&& script_url,
            ext::promise<void>&& promise,
            clients::client* client)
            -> job_t;

    auto schedule_job(
            const job_t& job)
            -> void;

    auto run_job(
            const job_queue_t& job_queue)
            -> void;

    auto finish_job(
            const job_t& job)
            -> void;

    auto resolve_job_promise(
            const job_t& job,
            const ext::any& value)
            -> void;

    auto reject_job_promise(
            const job_t& job)
            -> ext::tuple<ext::string, dom::detail::dom_exception_error_t>;

    auto start_register(
            ext::expected<url::detail::url_t> scope_url,
            ext::expected<url::detail::url_t> script_url,
            ext::promise<workers::service_worker_registration>& promise,
            service_worker_type_t* client,
            const url::detail::url_t& referrer,
            service_worker_type_t worker_type,
            update_via_cache_mode_t update_via_cache_mode)
            -> void;

    auto register_(
            const job_t& job)
            -> void;

    auto update(
            const job_t& job)
            -> void;

    auto handle_fetch(
            const fetch::detail::request_t& request,
            const fetch::detail::fetch_controller_t& controller,
            ext::boolean use_high_res_performance_timers)
            -> fetch::detail::response_t;

    auto unregister(
            const job_t& job)
            -> void;
}


struct service_workers::detail::job_t
{
    job_type_t job_type;
    storage::detail::storage_key_t storage_key;
    url::detail::url_t scope_url;
    url::detail::url_t script_url;
    service_worker_type_t worker_type;
    update_via_cache_mode_t update_via_cache_mode;
    clients::client* client;
    url::detail::url_t referrer;
    ext::promise<void> job_promise;
    job_queue_t& containing_job_queue;
    ext::vector<job_t>& list_of_equivalent_jobs;
    ext::boolean force_bypass_cache_flag;

    auto operator==(const job_t& other) -> ext::boolean;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_JOB_INTERNALS_HPP
