#include "navigation_preload_manager.hpp"
#include "navigation_preload_manager_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(service_workers)

#include "dom/other/dom_exception.hpp"
#include "service_workers/workers/service_worker_registration.hpp"


auto service_workers::other::navigation_preload_manager::enable()
        -> ext::promise<void>
{
    ACCESS_PIMPL(navigation_preload_manager);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    GO [d, &promise]
    {
        decltype(auto) registration = d->service_worker_registration.get();
        return_if (!registration->d_func()->active_worker) promise.reject(dom::other::dom_exception{"TODO", INVALID_STATE_ERR});
        registration->d_func()->navigation_preload_enabled_flag = true;
        promise.resolve();
    };

    return promise;
}


auto service_workers::other::navigation_preload_manager::disable()
        -> ext::promise<void>
{
    ACCESS_PIMPL(navigation_preload_manager);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    GO [d, &promise]
    {
        decltype(auto) registration = d->service_worker_registration.get();
        return_if (!registration->d_func()->active_worker) promise.reject(dom::other::dom_exception{"TODO", INVALID_STATE_ERR});
        registration->d_func()->navigation_preload_enabled_flag = false;
        promise.resolve();
    };

    return promise;
}


auto service_workers::other::navigation_preload_manager::set_header_value(
        ext::string&& value)
        -> ext::promise<void>
{
    ACCESS_PIMPL(navigation_preload_manager);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    GO [d, &promise, value = std::move(value)] mutable
    {
        decltype(auto) registration = d->service_worker_registration.get();
        return_if (!registration->d_func()->active_worker) promise.reject(dom::other::dom_exception{"TODO", INVALID_STATE_ERR});
        registration->d_func()->navigation_preload_header_value = std::move(value);
        promise.resolve();
    };

    return promise;
}


auto service_workers::other::navigation_preload_manager::get_state()
        -> ext::promise<detail::navigation_preload_state_t>
{
    ACCESS_PIMPL(navigation_preload_manager);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    GO [d]
    {
        decltype(auto) registration = d->service_worker_registration.get();
        auto state = detail::navigation_preload_state_t{};
        state.emplace("enabled", registration->d_func()->navigation_preload_enabled_flag);
        state.emplace("headerValue", registration->d_func()->navigation_preload_header_value);
    };
}
