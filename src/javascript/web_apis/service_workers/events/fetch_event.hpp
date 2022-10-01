#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_HPP

#include "service_workers/events/extendable_event.hpp"
namespace service_workers::events {class fetch_event;}
namespace fetch {class request; class response;}

#include "fetch_event_private.hpp"


class service_workers::events::fetch_event
        : public extendable_event
{
public constructors:
    fetch_event() = default;
    fetch_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(fetch_event);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto respond_with(ext::promise<fetch::response*>&& r) -> void;

private js_properties:
    DEFINE_GETTER(request, fetch::request*);
    DEFINE_GETTER(preload_response, const ext::promise<ext::any>&);
    DEFINE_GETTER(handled, const ext::promise<void>&);
    DEFINE_GETTER(client_id, ext::string_view);
    DEFINE_GETTER(resulting_client_id, ext::string_view);
    DEFINE_GETTER(replaces_client_id, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_HPP
