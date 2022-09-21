#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_HPP

#include "dom/nodes/event_target.hpp"
namespace service_workers::workers {class service_worker_container;}

#include "ext/promise.hpp"
#include <memory>
#include INCLUDE_INNER_TYPES(service_workers)
namespace service_workers::workers {class service_worker;}
namespace service_workers::workers {class service_worker_registration;}

class service_workers::workers::service_worker_container
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(service_worker_container);
    service_worker_container() = default;

public js_methods:
    auto register(const ext::string& script_url, detail::registration_options_t&& options = {}) -> ext::promise<service_worker_registration>;
    auto get_registration(const ext::string& client_url = "") -> ext::promise<service_worker_registration*>;
    auto get_registrations() -> ext::promise<const ext::vector<service_worker_registration>>;
    auto start_messages() -> void;

public js_properties:
    ext::property<std::unique_ptr<service_worker>> controller;
    ext::property<ext::promise<std::unique_ptr<service_worker_registration>>> ready;

private cpp_properties:
    std::unique_ptr<detail::service_worker_t> m_service_worker_client;
    ext::promise<void> ready_promise;
    // TODO : task queue ???

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(controller);
    DEFINE_CUSTOM_GETTER(ready);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_HPP
