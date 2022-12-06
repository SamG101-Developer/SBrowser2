#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_HPP


namespace service_workers::workers {class service_worker;}
namespace service_workers::workers {class service_worker_private;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(service_workers)


class service_workers::workers::service_worker
        : public dom::nodes::event_target
        , html::mixins::abstract_worker
{
public constructors:
    DOM_CTORS(service_worker);
    MAKE_PIMPL(service_worker);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto post_message(ext::any&& message, ext::vector<ext::any>&& transfer) -> void;
    auto post_message(ext::any&& message, html::detail::structured_serialize_options_t&& options = {}) -> void;

private js_properties:
    DEFINE_GETTER(script_url, ext::string);
    DEFINE_GETTER(state, detail::service_worker_state_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_WORKERS_SERVICE_WORKER_HPP
