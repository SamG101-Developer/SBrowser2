#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_CHANGE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_CHANGE_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "service_workers/events/extendable_event_private.hpp"

namespace push_api {class push_subscription;}


DEFINE_PRIVATE_CLASS(push_api, push_subscription_change_event) : service_workers::events::extendable_event_private
{
    std::unique_ptr<push_subscription> old_subscription;
    std::unique_ptr<push_subscription> new_subscription;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_CHANGE_EVENT_PRIVATE_HPP
