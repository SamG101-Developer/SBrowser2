#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "service_workers/clients/client_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(page_visibility)


DEFINE_PRIVATE_CLASS(service_workers::clients, window_client) : service_workers::clients::client_private
{
    html::detail::browsing_context_t* browsing_context;
    page_visibility::detail::visibility_state_t visibility_state;
    ext::boolean focus_state = false;
    ext::vector<ext::string> ancestor_origins_array;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_WINDOW_CLIENT_PRIVATE_HPP
