#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_REQUEST_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_REQUEST_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "service_workers/events/extendable_event_private.hpp"

namespace payment::request {class payment_request;}


DEFINE_PRIVATE_CLASS(payment::handler, payment_request_event) : service_workers::events::extendable_event_private
{
    ext::string top_origin;
    ext::string payment_request_origin;
    request::payment_request* payment_request;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_REQUEST_EVENT_PRIVATE_HPP
