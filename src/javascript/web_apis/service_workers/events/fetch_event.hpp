#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_HPP

#include "service_workers/events/extendable_event.hpp"
namespace service_workers::events {class fetch_event;}
namespace fetch {class request; class response;}


class service_workers::events::fetch_event
        : public extendable_event
{
public constructors:
    DOM_CTORS(fetch_event);
    fetch_event() = default;
    fetch_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto respond_with(ext::promise<fetch::response*> r) -> void;

public js_properties:
    ext::property<std::unique_ptr<fetch::request>> request;
    ext::property<ext::promise<ext::any>> preload_response;
    ext::property<ext::promise<void>> handled;
    ext::property<ext::string> client_id;
    ext::property<ext::string> resulting_client_id;
    ext::property<ext::string> replaces_client_id;

private cpp_properties:
    std::unique_ptr<fetch::response> m_potential_response;
    ext::boolean wait_to_response_flag;
    ext::boolean respond_with_entered_flag;
    ext::boolean respond_with_error_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_HPP
