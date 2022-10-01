#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(service_workers)
#include "ext/boolean.hpp"


DEFINE_PRIVATE_CLASS(service_workers::clients, client) : dom_object_private
{
    std::unique_ptr<detail::service_worker_client_t> service_worker_client;
    detail::frame_type_t frame_type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENT_PRIVATE_HPP
