#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/events/event_private.hpp"

#include "ext/boolean.ixx"


DEFINE_PRIVATE_CLASS(payment::request, payment_request_update_event) : dom::events::event_private
{
    ext::boolean wait_for_update;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_PRIVATE_HPP
