#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "service_workers/events/extendable_event_private.hpp"

namespace fetch {class request;}


DEFINE_PRIVATE_CLASS(service_workers::events, fetch_event) : extendable_event_private
{
    std::unique_ptr<fetch::request> request;
    ext::string client_id;
    ext::string resulting_client_id;
    ext::string replaces_client_id;
    ext::promise<ext::any> preload_response;
    ext::promise<void> handled;

    ext::boolean wait_to_response_flag;
    ext::boolean respond_with_entered_flag;
    ext::boolean respond_with_error_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_FETCH_EVENT_PRIVATE_HPP
