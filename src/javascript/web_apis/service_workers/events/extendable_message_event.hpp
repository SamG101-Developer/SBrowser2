#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_HPP

#include "service_workers/events/extendable_event.hpp"
namespace service_workers::events {class extendable_message_event;}

#include "ext/ranges.hpp"
#include "ext/span.hpp"
#include "extendable_message_event_private.hpp"
namespace html::messaging {class message_port;}
namespace service_workers::clients {class client;}
namespace service_workers::workers {class service_worker;}


class service_workers::events::extendable_message_event
        : public extendable_event
{
public constructors:
    extendable_message_event();
    extendable_message_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(extendable_message_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(data, const ext::any&);
    DEFINE_GETTER(origin, ext::string_view);
    DEFINE_GETTER(last_event_id, ext::string_view);
    DEFINE_GETTER(source, ext::variant<clients::client* COMMA workers::service_worker* COMMA html::messaging::message_port*>);
    DEFINE_GETTER(ports, ranges::any_helpful_view<html::messaging::message_port*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_EVENTS_EXTENDABLE_MESSAGE_EVENT_HPP
