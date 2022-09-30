#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

namespace service_workers::workers {class service_worker_registration;}


DEFINE_PRIVATE_CLASS(service_workers::other, navigation_preload_manager) : virtual dom_object_private
{
    std::unique_ptr<workers::service_worker_registration> service_worker_registration;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_PRIVATE_HPP
