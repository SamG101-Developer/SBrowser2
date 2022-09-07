#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_HPP

#include "dom/nodes/event_target.hpp"
namespace payment::request {class payment_request;}

#include "ext/promise.hpp"
#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include USE_INNER_TYPES(payment_request)
namespace payment::request {class payment_details_base;}
namespace payment::request {class payment_response;}


class payment::request::payment_request
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(request);
    request() = default;
    request(const ext::vector<detail::payment_method_data_t*>&, detail::payment_method_init_t&& details);

public js_methods:
    auto show(ext::optional<ext::promise<detail::payment_details_update_t>&> details_promise = ext::nullopt) -> ext::promise<payment_response>;
    auto abort() -> ext::promise<void>;
    auto can_make_payment() -> ext::promise<ext::boolean>;

public js_properties:
    ext::property<ext::string> id;

private js_slots:
    ext::slot<ext::string> s_serialized_method_data;
    ext::slot<ext::vector<ext::string>> s_serialized_modifier_data;
    ext::slot<payment_details_base*> s_details;
    ext::slot<detail::state_t> s_state;
    ext::slot<ext::boolean> s_updating;
    ext::slot<ext::promise<void>> s_accept_promise;
    ext::slot<payment_response*> s_response;
    ext::slot<detail::payment_handler_t<>*> s_handler;

private cpp_accessors:
    DEFINE_GETTER(id);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_REQUEST_PAYMENT_REQUEST_HPP
