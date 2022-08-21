#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_HPP

#include "dom/events/event.hpp"
namespace service_workers::events {class extendable_event;}

#include <future>


class service_workers::events::extendable_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(extendable_event);
    extendable_event() = default;
    extendable_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto wait_until(std::promise<ext::any>&& f);

private cpp_properties:
    ext:vector<std::promise<ext::any>> m_extend_lifetime_promises;
    ext::number<size_t> m_pending_promises_count;
    ext::boolean timed_out_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_HPP
