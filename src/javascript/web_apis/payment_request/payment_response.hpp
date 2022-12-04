#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_HPP

#include "dom/nodes/event_target.hpp"
namespace payment::request {class payment_response;};
namespace payment::request {class payment_response_private;};


#include INCLUDE_INNER_TYPES(payment_request)
namespace payment::request {class payment_request;};


class payment::request::payment_response
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(payment_response);
    MAKE_PIMPL(payment_response);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

public js_methods:
    auto complete(detail::payment_complete_t result = detail::payment_complete_t::UNKNOWN, detail::payment_complete_details_t&& details = {}) -> ext::promise<void>;
    auto retry(detail::payment_validation_errors_t&& error_fields = {}) -> ext::promise<void>;

private js_properties:
    DEFINE_GETTER(request_id, ext::string);
    DEFINE_GETTER(method_name, ext::string);
    DEFINE_GETTER(details, void*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_RESPONSE_HPP
