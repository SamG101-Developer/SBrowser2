#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "service_workers/events/extendable_event_private.hpp"

#include "ext/variant.ixx"
#include "ext/vector.hpp"
namespace service_workers::clients {class client;}
namespace service_workers::workers {class service_worker;}
namespace html::messaging {class message_port;}


DEFINE_PRIVATE_CLASS(service_workers::events, extendable_message_event) : extendable_event_private
{
    ext::any data;
    ext::string origin;
    ext::string last_event_id;
    ext::variant<clients::client*, workers::service_worker*, html::messaging::message_port*> source;
    ext::vector<std::unique_ptr<html::messaging::message_port>> ports;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_PRIVATE_HPP
