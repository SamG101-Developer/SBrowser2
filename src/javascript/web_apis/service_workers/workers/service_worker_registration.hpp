#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_HPP

#include "dom/nodes/event_target.hpp"
namespace service_workers::workers {class service_worker_registration;}

#include "ext/promise.hpp"
#include <memory>
#include USE_INNER_TYPES(notifications)
#include USE_INNER_TYPES(service_workers)
namespace notifications {class notification;}
namespace service_workers::other {class navigation_preload_manager;}
namespace service_workers::workers {class service_worker;}

class service_workers::workers::service_worker_registration
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(service_worker_registration);
    service_worker_registration() = default;

public js_methods:
    auto update() -> ext::promise<void>;
    auto unregister() -> ext::promise<ext::boolean>;

    /* NOTIFICATIONS */
    auto show_notification(ext::string&& title, notifications::detail::notification_options_t&& options = {}) -> ext::promise<void>;
    auto show_notifications(notifications::detail::get_notification_options_t&& options = {}) -> ext::promise<ext::vector<notifications::notification*>>;

public js_properties:
    ext::property<std::unique_ptr<service_worker>> installing;
    ext::property<std::unique_ptr<service_worker>> waiting;
    ext::property<std::unique_ptr<service_worker>> active;
    ext::property<std::unique_ptr<other::navigation_preload_manager>> navigation_preload;

    ext::property<ext::string> scope;
    ext::property<std::unique_ptr<detail::service_worker_update_via_cache_t>> update_via_cache;

private cpp_properties:
    std::unique_ptr<detail::service_worker_registration_t> m_service_worker_registration;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_HPP
