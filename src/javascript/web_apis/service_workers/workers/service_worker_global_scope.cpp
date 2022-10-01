#include "service_worker_global_scope.hpp"

#include "service_workers/detail/service_worker_internals.hpp"
#include "service_workers/workers/service_worker.hpp"


auto service_workers::workers::service_worker_global_scope::skip_waiting()
        -> ext::promise<void>
{
    ACCESS_PIMPL(const service_worker_global_scope);
    auto promise = ext::promise<void>{};

    GO [d, &promise]
    {
        d->service_worker->d_func()->skip_waiting_flag = true;
        detail::try_activate(d->service_worker->d_func()->containing_worker_registration);
        promise.resolve();
    };

    return promise;
}


auto service_workers::workers::service_worker_global_scope::get_clients() const -> clients::clients*
{
    ACCESS_PIMPL(const service_worker_global_scope);
    return d->clients.get();
}


auto service_workers::workers::service_worker_global_scope::get_registration() const -> service_worker_registration*
{
    ACCESS_PIMPL(const service_worker_global_scope);
    JS_REALM_GET_RELEVANT(this);
    return detail::get_service_worker_registration(
            this_relevant_settings_object,
            d->service_worker->d_func()->containing_worker_registration);
}


auto service_workers::workers::service_worker_global_scope::get_service_worker() const -> service_worker*
{
    ACCESS_PIMPL(const service_worker_global_scope);
    JS_REALM_GET_RELEVANT(this);
    return detail::get_service_worker_object(
            this_relevant_settings_object,
            d->service_worker.get());
}
