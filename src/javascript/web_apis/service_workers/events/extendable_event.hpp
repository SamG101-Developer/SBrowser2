#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_HPP

#include "dom/events/event.hpp"
namespace service_workers::events {class extendable_event;}
namespace service_workers::events {class extendable_event_private;}

#include "ext/promise.hpp"


class service_workers::events::extendable_event
        : public dom::events::event
{
public constructors:
    extendable_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(extendable_event);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto wait_until(ext::promise<ext::any>&& f) -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_EVENT_HPP
