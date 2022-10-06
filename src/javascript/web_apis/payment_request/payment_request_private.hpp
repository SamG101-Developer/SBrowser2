#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(payment_request)
#include "ext/uuid.hpp"
#include "ext/promise.hpp"
namespace payment::request {class payment_response;}


DEFINE_PRIVATE_CLASS(payment::request, payment_request) : dom::nodes::event_target_private
{
    ext::uuid id;

    ext::string serialized_method_data;
    ext::vector<ext::string> serialized_modifier_data;
    detail::payment_details_base_t details;
    detail::state_t state;
    ext::boolean updating;
    ext::promise<void> accept_promise;
    payment_response* response;
    detail::payment_handler_t<>* handler;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_PRIVATE_HPP
