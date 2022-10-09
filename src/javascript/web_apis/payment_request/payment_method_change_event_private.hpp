#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_METHOD_CHANGE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_METHOD_CHANGE_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "payment_request/payment_request_update_event_private.hpp"


DEFINE_PRIVATE_CLASS(payment::request, payment_method_change_event) : payment_request_update_event_private
{
    ext::string method_name;
    ext::string method_details;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_METHOD_CHANGE_EVENT_PRIVATE_HPP
