#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "service_workers/events/extendable_event_private.hpp"

#include INCLUDE_INNER_TYPES(payment_handler)


DEFINE_PRIVATE_CLASS(payment::handler, can_make_payment_event) : service_workers::events::extendable_event_private
{
    ext::string top_origin;
    ext::string payment_request_origin;
    ext::vector<detail::payment_method_data_t> method_data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_PRIVATE_HPP
