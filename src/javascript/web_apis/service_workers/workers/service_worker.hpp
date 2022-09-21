#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_HPP

#include "dom/nodes/event_target.hpp"
namespace service_workers::workers {class service_worker;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(service_workers)

class service_workers::workers::service_worker
        : public dom::nodes::event_target
        , public html::mixins::abstract_worker
{
public constructors:
    DOM_CTORS(service_worker);
    service_worker() = default;

public js_methods:
    auto post_message(const ext::any& message, const ext::vector<ext::any>& transfer) -> void;
    auto post_message(const ext::any& message, html::detail::structure_serialize_options_t&& options = {}) -> void;

public js_properties:
    ext::property<ext::string> script_url;
    ext::property<detail::service_worker_state_t> state;

private cpp_properties:
    std::unique_ptr<detail::service_worker_t> m_service_worker;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_HPP
