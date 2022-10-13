#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_CHANGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_CHANGE_EVENT_HPP

// Inheritance Includes & This Class
#include "service_workers/events/extendable_event.hpp"
namespace push_api {class push_subscription_change_event;}
namespace push_api {class push_subscription_change_event_private;}

// Other Includes & Forward Declarations
namespace push_api {class push_subscription;}


class push_api::push_subscription_change_event
        : public service_workers::events::extendable_event
{
public constructors:
    push_subscription_change_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(push_subscription_change_event);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(old_subscription, push_subscription*);
    DEFINE_GETTER(new_subscription, push_subscription*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_CHANGE_EVENT_HPP
