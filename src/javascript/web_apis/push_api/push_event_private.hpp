#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "service_workers/events/extendable_event_private.hpp"

namespace push_api {class push_message_data;}


DEFINE_PRIVATE_CLASS(push_api, push_event) : service_workers::events::extendable_event_private
{
    std::unique_ptr<push_message_data> data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_EVENT_PRIVATE_HPP
