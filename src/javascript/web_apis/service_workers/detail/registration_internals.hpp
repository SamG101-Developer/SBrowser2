#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_REGISTRATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_REGISTRATION_INTERNALS_HPP

#include "ext/optional.hpp"
#include "url/url.hpp"
#include USE_INNER_TYPES(service_workers)

namespace service_workers::detail
{
    auto set_registration(
            const storage::detail::storage_key_t& storage_key,
            const url::url_object& url,
            update_via_cache_mode_t update_via_cache_mode)
            -> service_worker_registration_t;

    auto clear_registration(
            const service_worker_registration_t& registration)
            -> void;

    auto try_clear_registration(
            const service_worker_registration_t& registration)
            -> void;

    auto update_registration_state(
            const service_worker_registration_t& registration,
            target_t target,
            ext::optional<service_worker_t&> service_worker)
            -> void;

    auto match_service_worker_registration(
            const storage::detail::storage_key_t& storage_key,
            const url::url_object& url)
            -> service_worker_registration_t&;

    auto get_registration(
            const storage::detail::storage_key_t& storage_key,
            const url::url_object& url)
            -> service_worker_registration_t&;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_REGISTRATION_INTERNALS_HPP
