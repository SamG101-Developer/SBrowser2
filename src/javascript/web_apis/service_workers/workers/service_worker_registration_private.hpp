#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(service_workers)
#include INCLUDE_INNER_TYPES(url)
namespace payment::handler {class payment_manager;}
namespace push_api {class push_manager;}
namespace service_workers::other {class navigation_preload_manager;}
namespace service_workers::workers {class service_worker;}


DEFINE_PRIVATE_CLASS(service_workers::workers, service_worker_registration) : dom::nodes::event_target_private
{
    storage::detail::storage_key_t storage_key;
    std::unique_ptr<url::detail::url_t> scope_url;
    service_worker* installing_worker;
    service_worker* waiting_worker;
    service_worker* active_worker;

    ext::number<int> last_update_check_time;
    detail::update_via_cache_mode_t update_via_cache_mode = detail::update_via_cache_mode_t::IMPORTS;
    ext::vector<html::detail::task_queue_t> task_queues;

    other::navigation_preload_manager* navigation_preload_manager;
    ext::boolean navigation_preload_enabled_flag;
    ext::string navigation_preload_header_value = u8"true";

    /* [PAYMENT-HANDLER] */
    std::unique_ptr<payment::handler::payment_manager> payment_manager;

    /* [PUSH-API] */
    std::unique_ptr<push_api::push_manager> push_manager;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_REGISTRATION_PRIVATE_HPP
