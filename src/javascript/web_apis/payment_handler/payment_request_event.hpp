#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_REQUEST_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_REQUEST_EVENT_HPP

#include "payment_handler/can_make_payment_event.hpp"
namespace payment::handler {class payment_request_event;}

#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(payment_handler)
#include INCLUDE_INNER_TYPES(payment_request)
namespace payment::handler {class window_client;}


class payment::handler::payment_request_event
        : public can_make_payment_event
{
public constructors:
    payment_request_event() = default;
    payment_request_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto open_window(ext::string_view url) -> ext::promise<window_client*>;
    auto change_payment_method(ext::string_view method_name, ext::map<ext::string, ext::any>&& options = {}); // TODO: detail::payment_request_update_t
    auto respond_with(ext::promise<detail::payment_handler_reponse_t> handler_response_promise) -> void;

private js_properties:
    ext::property<ext::string> payment_request_id;
    ext::property<std::unique_ptr<void>> total;
    ext::property<const ext::vector<detail::payment_details_modifier_t>> modifiers;

private js_slots:
    ext::slot<std::unique_ptr<window_client>> s_window_client;
    ext::slot<std::unique_ptr<void>> s_fetched_image; // TODO: type
    ext::slot<ext::boolean> s_response_with_called; // TODO: type
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_REQUEST_EVENT_HPP
