#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_NOTIFICATION_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_NOTIFICATION_EVENT_HPP

#include "service_workers/events/extendable_event.hpp"
namespace notifications {class notification_event;}

namespace notifications {class notification;}


class notifications::notification_event
        : public service_workers::events::extendable_event
{
public constructors:
    DOM_CTORS(notification_event);
    notification_event() = default;
    notification_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<std::unique_ptr<notification>> notification;
    ext::property<ext::string> action;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_NOTIFICATIONS_NOTIFICATION_EVENT_HPP
