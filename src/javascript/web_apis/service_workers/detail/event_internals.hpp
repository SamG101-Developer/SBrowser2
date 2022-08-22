#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_EVENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_EVENT_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include <future>
#include USE_INNER_TYPES(service_workers)
namespace service_workers::events {class extendable_event;}

namespace service_workers::detail
{
    auto active(
            events::extendable_event* event)
            -> ext::boolean;

    auto add_lifetime_promise(
            std::promise<ext::any>&& promise,
            events::extendable_event* event)
            -> void;

    auto should_skip_event(
            ext::string&& event_name,
            const service_worker_t& worker)
            -> ext::boolean;

    template <inherit<events::extendable_event> T, callable F0, callable F1>
    auto fire_functional_event(
            ext::string&& event_name,
            const service_worker_registration_t& registration,
            F0&& initialization_steps,
            F1&& post_dispatch_steps)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_EVENT_INTERNALS_HPP
