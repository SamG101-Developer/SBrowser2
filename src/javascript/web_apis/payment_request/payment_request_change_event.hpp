#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_CHANGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_CHANGE_EVENT_HPP

#include "dom/events/event.hpp"
namespace payment_request {class payment_request_change_event;}


class payment_request::payment_request_change_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(payment_request_change_event);
    payment_request_change_event() = default;
    payment_request_change_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::string> method_name;
    ext::property<ext::string> method_details;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_CHANGE_EVENT_HPP
