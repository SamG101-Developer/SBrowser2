#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event_private.hpp"

#include "ext/any.hpp"
#include "ext/promise.hpp"
#include "ext/vector.hpp"


DEFINE_PRIVATE_CLASS(service_workers::events, extendable_event) : dom::events::event_private
{
    ext::vector<ext::promise<ext::any>> extend_lifetime_promises;
    ext::number<int> pending_promises_count = 0;
    ext::boolean timed_out_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_PRIVATE_HPP
