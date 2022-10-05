#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(payment_request)
#include "ext/promise.hpp"
namespace payment::request {class payment_response;}


DEFINE_PRIVATE_CLASS(payment::request, payment_request_private) : dom::nodes::event_target_private
{
    ext::string s_serialized_method_data;
    ext::vector<ext::string> s_serialized_modifier_data;
    detail::payment_details_base_t s_details;
    detail::state_t s_state;
    ext::boolean s_updating;
    ext::promise<void> s_accept_promise;
    payment_response* s_response;
    detail::payment_handler_t<>* s_handler;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_PRIVATE_HPP
