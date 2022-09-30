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

#include "service_worker_container_private.hpp"


class service_workers::workers::service_worker_container
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(service_worker_container);
    MAKE_PIMPL(service_worker_container);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto register_(ext::string_view script_url, detail::registration_options_t&& options = {}) -> ext::promise<service_worker_registration>;
    auto get_registration(const ext::string& client_url = "") -> ext::promise<service_worker_registration*>;
    auto get_registrations() -> ext::promise<const ext::vector<service_worker_registration>>;
    auto start_messages() -> void;

private js_properties:
    DEFINE_GETTER(controller, service_worker*);
    DEFINE_GETTER(ready, ext::promise<service_worker_registration*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_CONTAINER_HPP
