#include "service_worker_registration.hpp"
#include "service_worker_registration_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(service_workers)


#include "service_workers/detail/job_internals.hpp"
#include "service_workers/detail/service_worker_internals.hpp"
#include "service_workers/workers/service_worker.hpp"
#include "service_workers/workers/service_worker_global_scope.hpp"
#include "url/detail/url_internals.hpp"


service_workers::workers::service_worker_registration::service_worker_registration()
{
    INIT_PIMPL(service_worker_registration);
}


auto service_workers::workers::service_worker_registration::update()
        -> ext::promise<void>
{
    ACCESS_PIMPL(service_worker_registration);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    auto e = js::env::env::relevant(this);
    decltype(auto) global_scope = e.cpp.global<service_worker_global_scope*>();
    decltype(auto) newest_worker = detail::get_newest_worker(this);

    return_if (!newest_worker) promise.reject(dom::other::dom_exception{u8"Must have a valid newest worker", INVALID_STATE_ERR});
    return_if (global_scope && global_scope->d_func()->service_worker->d_func()->state == detail::service_worker_state_t::INSTALLING) promise.reject(dom::other::dom_exception{u8"ServiceWorkerGlobalScope's worker cannot be installing", INVALID_STATE_ERR});

    auto job = detail::create_job(detail::job_type_t::UPDATE, d->storage_key, d->scope_url.get(), newest_worker->d_func()->script_url, promise, this_relevant_settings_object);
    job->worker_type = newest_worker->d_func()->type;
    detail::schedule_job(std::move(job));

    return promise;
}


auto service_workers::workers::service_worker_registration::unregister()
        -> ext::promise<ext::boolean>
{
    ACCESS_PIMPL(service_worker_registration);

    auto e = js::env::env::relevant(this);
    auto promise = ext::promise<ext::boolean>{};
    auto job = detail::create_job(detail::job_type_t::UNREGISTER, d->storage_key, *d->scope_url, nullptr, promise, e.js.settings());
    detail::schedule_job(std::move(job));

    return promise;
}


auto service_workers::workers::service_worker_registration::get_installing() const -> service_worker*
{
    ACCESS_PIMPL(const service_worker_registration);
    return d->installing_worker;
}


auto service_workers::workers::service_worker_registration::get_waiting() const -> service_worker*
{
    ACCESS_PIMPL(const service_worker_registration);
    return d->waiting_worker;
}


auto service_workers::workers::service_worker_registration::get_active() const -> service_worker*
{
    ACCESS_PIMPL(const service_worker_registration);
    return d->active_worker;
}


auto service_workers::workers::service_worker_registration::get_navigation_preload() const -> other::navigation_preload_manager*
{
    ACCESS_PIMPL(const service_worker_registration);
    return d->navigation_preload_manager;
}


auto service_workers::workers::service_worker_registration::get_scope() const -> ext::string
{
    ACCESS_PIMPL(const service_worker_registration);
    return url::detail::url_serializer(*d->scope_url);
}


auto service_workers::workers::service_worker_registration::get_update_via_cache() const -> detail::update_via_cache_mode_t
{
    ACCESS_PIMPL(const service_worker_registration);
    return d->update_via_cache_mode;
}


auto service_workers::workers::service_worker_registration::get_payment_manager() const -> payment::handler::payment_manager*
{
    /* [PAYMENT-HANDLER] */
    ACCESS_PIMPL(const service_worker_registration);
    return d->payment_manager.get();
}


auto service_workers::workers::service_worker_registration::get_push_manager() const -> push_api::push_manager*
{
    /* [PUSH-API] */
    ACCESS_PIMPL(const service_worker_registration);
    return d->push_manager.get();
}
