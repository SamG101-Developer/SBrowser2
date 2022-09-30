#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "service_workers/events/extendable_event_private.hpp"


DEFINE_PRIVATE_CLASS(payment::handler, can_make_payment_event) : service_workers::events::extendable_event_private {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_PRIVATE_HPP
