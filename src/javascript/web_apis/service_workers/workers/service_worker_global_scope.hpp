#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_HPP

#include "html/workers/worker_global_scope.hpp"
namespace service_workers::workers {class service_worker_global_scope;}
namespace service_workers::workers {class service_worker_global_scope_private;}


namespace service_workers::clients {class clients;}
namespace service_workers::workers {class service_worker;}
namespace service_workers::workers {class service_worker_registration;}


class service_workers::workers::service_worker_global_scope
        : public html::workers::worker_global_scope
{
public constructors:
    DOM_CTORS(service_worker_global_scope);
    MAKE_PIMPL(service_worker_global_scope);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto skip_waiting() -> ext::promise<void>;

private js_properties:
    DEFINE_GETTER(clients, clients::clients*);
    DEFINE_GETTER(registration, service_worker_registration*);
    DEFINE_GETTER(service_worker, service_worker*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_HPP
