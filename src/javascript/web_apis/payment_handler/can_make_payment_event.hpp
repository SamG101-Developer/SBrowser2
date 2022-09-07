#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_HPP

#include "dom/events/event.hpp"
namespace payment::handler {class can_make_payment_event;}

#include USE_INNER_TYPES(payment_request)
#include "ext/promise.hpp"


class payment::handler::can_make_payment_event
        : public dom::events::event
{
public constructors:
    can_make_payment_event() = default;
    can_make_payment_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto response_with(const ext::promise<ext::boolean>& can_make_payment_response) -> void;

public js_properties:
    ext::property<ext::string> top_origin;
    ext::property<ext::string> payment_request_origin;
    ext::property<const ext::vector<detail::payment_method_data_t>> method_data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_HPP
