#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_PRIVATE_HPP

#include "ext/pimpl.ixx"


namespace service_workers::workers {class service_worker_registration;}

DEFINE_PRIVATE_CLASS(push_api, push_manager) : virtual dom_object_private
{
    service_workers::workers::service_worker_registration* registration;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_PRIVATE_HPP
