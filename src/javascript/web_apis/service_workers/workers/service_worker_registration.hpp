#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_HPP


namespace service_workers::workers {class service_worker_registration;}
namespace service_workers::workers {class service_worker_registration_private;}


#include <memory>
#include INCLUDE_INNER_TYPES(notifications)
#include INCLUDE_INNER_TYPES(service_workers)
namespace notifications {class notification;}
namespace payment::handler {class payment_manager;}
namespace push_api {class push_manager;}
namespace service_workers::other {class navigation_preload_manager;}
namespace service_workers::workers {class service_worker;}


class service_workers::workers::service_worker_registration
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(service_worker_registration);
    MAKE_PIMPL(service_worker_registration);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto update() -> ext::promise<void>;
    auto unregister() -> ext::promise<ext::boolean>;

    /* [NOTIFICATIONS] */
    auto show_notification(ext::string&& title, notifications::detail::notification_options_t&& options = {}) -> ext::promise<void>;
    auto show_notifications(notifications::detail::get_notification_options_t&& options = {}) -> ext::promise<ext::vector<notifications::notification*>>;

private js_properties:
    DEFINE_GETTER(installing, service_worker*);
    DEFINE_GETTER(waiting, service_worker*);
    DEFINE_GETTER(active, service_worker*);
    DEFINE_GETTER(navigation_preload, other::navigation_preload_manager*);

    DEFINE_GETTER(scope, ext::string);
    DEFINE_GETTER(update_via_cache, detail::update_via_cache_mode_t);

    /* [PAYMENT-HANDLER] */
    DEFINE_GETTER(payment_manager, payment::handler::payment_manager*);

    /* [PUSH-API] */
    DEFINE_GETTER(push_manager, push_api::push_manager*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_HPP
