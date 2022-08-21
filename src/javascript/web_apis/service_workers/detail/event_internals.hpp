#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_EVENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_EVENT_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include <future>
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
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_EVENT_INTERNALS_HPP
