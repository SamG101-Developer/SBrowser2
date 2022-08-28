#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
namespace payment_request {class payment_request_update_event;}

#include <future>
#include USE_INNER_TYPES(payment_request)


class payment_request::payment_request_update_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(payment_request_update_event);
    payment_request_update_event() = default;
    payment_request_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto update_with(const std::promise<detail::payment_details_update_t>& details_promise) -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_HPP