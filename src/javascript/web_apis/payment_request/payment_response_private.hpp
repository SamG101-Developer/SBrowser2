#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/event_target_private.hpp"

#include "ext/optional.hpp"
#include "ext/promise.hpp"
namespace payment::request {class payment_request;}


DEFINE_PRIVATE_CLASS(payment::request, payment_response) : dom::nodes::event_target_private
{
    ext::boolean complete;
    payment_request* request;
    ext::optional<ext::promise<void>> retry_promise;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_PRIVATE_HPP
