#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_JOB_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_JOB_INTERNALS_HPP

#include <future>
#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "url/url.hpp"
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(storage)
#include USE_INNER_TYPES(service_workers)


namespace service_workers::detail
{

    auto is_bad_import_script_response(
            const fetch::detail::response_t&)
            -> ext::boolean;

    auto create_job(
            job_type_t job_type,
            storage::detail::storage_key_t&& storage_key,
            url::url_object&& scope_url,
            url::url_object&& script_url,
            std::promise<void>&& promise,
            service_worker_client_t&& client)
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
            -> ext::tuple<ext::string, v8_custom_error_t>;

    auto start_register(
            ext::optional<url::url_object> scope_url,
            ext::optional<url::url_object> script_url,
            const std::promise<void>& promise,
            const service_worker_client_t& client,
            const url::url_object& referrer,
            service_worker_type_t worker_type,
            update_via_cache_mode_t update_via_cache_mode)
            -> void;

    auto register_(
            const job_t& job)
            -> void;

}


struct service_workers::detail::job_t
{
    job_type_t job_type;
    storage::detail::storage_key_t storage_key;
    url::url_object scope_url;
    url::url_object script_url;
    service_worker_type_t worker_type;
    update_via_cache_mode_t update_via_cache_mode;
    service_worker_client_t& client;
    url::url_object referrer;
    std::promise<void> job_promise;
    job_queue_t& containing_job_queue;
    ext::vector<job_t>& list_of_equivalent_jobs;
    ext::boolean force_bypass_cache_flag;

    auto operator==(const job_t& other) -> ext::boolean;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_JOB_INTERNALS_HPP
