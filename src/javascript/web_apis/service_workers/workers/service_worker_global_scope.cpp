#include "service_worker_global_scope.hpp"
#include "service_worker_global_scope_private.hpp"

#include "service_workers/detail/service_worker_internals.hpp"
#include "service_workers/workers/service_worker.hpp"
#include "service_workers/workers/service_worker_private.hpp"

#include "web_idl/detail/type_mapping_internals.hpp"


auto service_workers::workers::service_worker_global_scope::skip_waiting()
        -> ext::promise<void>
{
    ACCESS_PIMPL(const service_worker_global_scope);
    auto promise = ext::promise<void>{};
    auto e = js::env::env::relevant(this);

    GO [d, &e, &promise]
    {
        d->service_worker->d_func()->skip_waiting_flag = true;
        detail::try_activate(*d->service_worker->d_func()->containing_worker_registration);
        web_idl::detail::resolve_promise(promise, e.js.realm());
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
    auto e = js::env::env::relevant(this);
    return detail::get_service_worker_registration(e.js.settings(), d->service_worker->d_func()->containing_worker_registration);
}


auto service_workers::workers::service_worker_global_scope::get_service_worker() const -> service_worker*
{
    ACCESS_PIMPL(const service_worker_global_scope);
    auto e = js::env::env::relevant(this);
    return detail::get_service_worker_object(e.js.settings(), *d->service_worker);
}
