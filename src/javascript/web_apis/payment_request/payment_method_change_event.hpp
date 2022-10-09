#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_METHOD_CHANGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_METHOD_CHANGE_EVENT_HPP

#include "payment_request/payment_request_update_event.hpp"
namespace payment::request {class payment_method_change_event;}
namespace payment::request {class payment_method_change_event_private;}


class payment::request::payment_method_change_event
        : public payment_request_update_event
{
public constructors:
    payment_method_change_event() = default;
    payment_method_change_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(payment_method_change_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(method_name, ext::string_view);
    DEFINE_GETTER(method_details, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_METHOD_CHANGE_EVENT_HPP
