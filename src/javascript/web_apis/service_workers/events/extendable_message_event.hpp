#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_HPP

#include "service_workers/events/extendable_event.hpp"
namespace service_workers::events {class extendable_message_event;}

namespace html::messaging {class message_port;}
namespace service_workers::clients {class client;}
namespace service_workers::workers {class service_worker;}


class service_workers::events::extendable_message_event
        : public extendable_event
{
public constructors:
    DOM_CTORS(extendable_message_event);
    extendable_message_event() = default;
    extendable_message_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<ext::any> data;
    ext::property<ext::string> origin;
    ext::property<ext::string> last_event_id;
    ext::property<ext::variant<clients::client*, workers::service_worker*, html::messaging::message_port*>> source;
    ext::property<const ext::vector<html::messaging::message_port*>> ports;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_HPP
