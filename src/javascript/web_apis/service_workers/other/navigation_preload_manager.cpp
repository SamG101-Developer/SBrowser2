#include "navigation_preload_manager.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/other/dom_exception.hpp"

#include "service_workers/workers/service_worker_registration.hpp"


auto service_workers::other::navigation_preload_manager::enable()
        -> ext::promise<void>
{
    ACCESS_PIMPL(navigation_preload_manager);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    go [d, &promise]
    {
        decltype(auto) registration = d->service_worker_registration.get();
        return_if (!registration->d_func()->active_worker) promise.reject(dom::other::dom_exception{"TODO", INVALID_STATE_ERR});
        registration.d_func()->navigation_preload_enabled_flag = true;
        promise.resolve();
    };

    return promise;
}
