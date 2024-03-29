#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_HPP


namespace payment::request {class payment_request_update_event;}
namespace payment::request {class payment_request_update_event_private;}


#include INCLUDE_INNER_TYPES(payment_request)


class payment::request::payment_request_update_event
        : public dom::events::event
{
public constructors:
    payment_request_update_event() = default;
    payment_request_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(payment_request_update_event);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto update_with(ext::promise<detail::payment_details_update_t>& details_promise) -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_UPDATE_EVENT_HPP
