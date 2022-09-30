#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace service_workers::clients {class client;}
namespace service_workers::workers {class service_worker_registration;}


DEFINE_PRIVATE_CLASS(service_workers::workers, service_worker_container) : dom::nodes::event_target_private
{
    clients::client* service_worker_client;
    ext::promise<service_worker_registration*> ready_promise;

    html::detail::task_queue_t client_message_queue;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_PRIVATE_HPP
