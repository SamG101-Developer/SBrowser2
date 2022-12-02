#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/workers/worker_global_scope_private.hpp"

#include "ext/boolean.ixx"
namespace service_workers::workers {class service_worker;}
namespace service_workers::clients {class clients;}


DEFINE_PRIVATE_CLASS(service_workers::workers, service_worker_global_scope) : html::workers::worker_global_scope_private
{
    std::unique_ptr<service_worker> service_worker;
    std::unique_ptr<clients::clients> clients;
    ext::boolean force_bypass_cache_for_import_scripts_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
