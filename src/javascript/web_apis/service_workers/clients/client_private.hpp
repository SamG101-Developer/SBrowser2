#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/boolean.hpp"


DEFINE_PRIVATE_CLASS(service_workers::clients, client) : dom_object_private
{
    ext::boolean discarded_flag;

    client_private() {environment_discarding_steps = [this] {discarded_flag = true;};}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENT_PRIVATE_HPP
