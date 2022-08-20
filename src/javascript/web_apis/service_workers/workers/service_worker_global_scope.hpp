#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_HPP

#include "html/workers/worker_global_scope.hpp"
namespace service_workers::workers {class service_worker_global_scope;}

#include <future>
namespace service_workers::clients {class clients;}
namespace service_workers::workers {class service_worker;}
namespace service_workers::workers {class service_worker_registration;}


class service_workers::workers::service_worker_global_scope
        : public html::workers::worker_global_scope
{
public constructors:
    DOM_CTORS(service_worker_global_scope);
    service_worker_global_scope() = default;

public js_methods:
    auto skip_waiting() -> std::promise<void>;

public js_properties:
    ext::property<std::unique_ptr<clients::clients>> clients;
    ext::property<std::unique_ptr<service_worker_registration>> registration;
    ext::property<std::unique_ptr<service_worker>> service_worker;

public cpp_properties:
    std::unique_ptr<class service_worker> m_service_worker;
    ext::boolean m_force_bypass_cache_for_import_scripts_flag = false;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_HPP
