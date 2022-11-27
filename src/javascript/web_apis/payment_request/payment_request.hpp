#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_HPP

#include "dom/nodes/event_target.hpp"
namespace payment::request {class payment_request;}
namespace payment::request {class payment_request_private;}

#include "ext/promise.hpp"
#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "ext/span.hpp"
#include INCLUDE_INNER_TYPES(payment_request)
namespace payment::request {class payment_response;}


class payment::request::payment_request
        : public dom::nodes::event_target
{
public constructors:
    payment_request(ext::vector_span<detail::payment_method_data_t*> method_data, detail::payment_method_init_t&& details);
    DOM_CTORS(payment_request);
    MAKE_PIMPL(payment_request);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto show(ext::optional<ext::promise<detail::payment_details_update_t>&> details_promise = ext::nullopt) -> ext::promise<payment_response>;
    auto abort() -> ext::promise<void>;
    auto can_make_payment() -> ext::promise<ext::boolean>;

private js_properties:
    DEFINE_GETTER(id, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_HPP
