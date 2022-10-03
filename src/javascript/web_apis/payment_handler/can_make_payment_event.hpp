#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_HPP

#include "service_workers/events/extendable_event.hpp"
namespace payment::handler {class can_make_payment_event;}

#include INCLUDE_INNER_TYPES(payment_request)
#include "ext/promise.hpp"
#include "ext/span.hpp"

#include "can_make_payment_event_private.hpp"


class payment::handler::can_make_payment_event
        : public service_workers::events::extendable_event
{
public constructors:
    can_make_payment_event() = default;
    can_make_payment_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(can_make_payment_event);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto response_with(const ext::promise<ext::boolean>& can_make_payment_response) -> void;

private js_properties:
    DEFINE_GETTER(top_origin, ext::string_view);
    DEFINE_GETTER(payment_request_origin, ext::string_view);
    DEFINE_GETTER(method_data, ext::vector_span<detail::payment_method_data_t>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_CAN_MAKE_PAYMENT_EVENT_HPP
