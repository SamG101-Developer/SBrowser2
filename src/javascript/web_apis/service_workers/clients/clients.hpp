#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENTS_HPP

#include "dom_object.hpp"
namespace service_workers::clients {class clients;}

#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <future>
#include USE_INNER_TYPES(service_workers)
namespace service_workers::clients {class client;}
namespace service_workers::clients {class window_client;}

class service_workers::clients::clients
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(clients);
    clients() = default;

public js_methods:
    auto get(ext::string_view id) -> ext::variant<std::promise<void>, std::promise<client>>;
    auto match_all(detail::client_query_options_t&& options = {}) -> std::promise<const ext::vector<client*>>;
    auto open_window(ext::string_view url) -> std::promise<window_client>;
    auto claim() -> std::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENTS_HPP
