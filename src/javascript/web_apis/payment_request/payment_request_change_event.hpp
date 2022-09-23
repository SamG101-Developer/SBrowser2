#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_CHANGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_CHANGE_EVENT_HPP

#include "dom/events/event.hpp"
namespace payment::request {class payment_request_change_event;}


class payment::request::payment_request_change_event
        : public dom::events::event
{
public constructors:
    payment_request_change_event() = default;
    payment_request_change_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<ext::string> method_name;
    ext::property<ext::string> method_details;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_CHANGE_EVENT_HPP
