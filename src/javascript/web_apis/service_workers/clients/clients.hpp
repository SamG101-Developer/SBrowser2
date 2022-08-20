#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENTS_HPP

#include "dom_object.hpp"
namespace service_workers::clients {class clients;}

#include "ext/variant.hpp"
#include <future>
namespace service_workers::clients {class client;}

class service_workers::clients::clients
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(clients);
    clients() = default;

public js_methods:
    auto get(ext::string_view id) -> ext::variant<std::promise<void>, std::promise<client>>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CLIENTS_CLIENTS_HPP
