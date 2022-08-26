#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_HPP

#include "dom/nodes/event_target.hpp"
namespace payment_request {class payment_response;};

#include <future>
#include USE_INNER_TYPES(payment_request)
namespace payment_request {class payment_request;};


class payment_request::payment_response
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(payment_response);
    payment_response() = default;

public js_methods:
    auto complete(detail::payment_complete_t result = detail::payment_complete_t::UNKNOWN, detail::payment_complete_details_t&& details = {}) -> std::promise<void>;
    auto retry(detail::payment_validation_errors_t&& error_fields = {}) -> std::promise<void>;

public js_properties:
    ext::property<ext::string> request_id;
    ext::property<ext::string> method_name;
    ext::property<void*> details;

public cpp_methods:
    auto to_json() const -> ext::string override;

private js_slots:
    ext::slot<ext::boolean> s_complete;
    ext::slot<payment_request*> s_request;
    ext::slot<std::promise<void>> s_retry_promise;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_HPP
