#include "payment_request_update_event.hpp"
#include "detail/payment_internals.hpp"
#include "payment_request_update_event_private.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"

#include "payment_request/payment_method_change_event.hpp"
#include "payment_request/payment_method_change_event_private.hpp"
#include "payment_request/payment_request.hpp"
#include "payment_request/payment_request_private.hpp"
#include "payment_request/payment_response.hpp"
#include "payment_request/payment_response_private.hpp"


payment::request::payment_request_update_event::payment_request_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(payment_request_update_event);
    ACCESS_PIMPL(payment_request_update_event);

    d->wait_for_update = false;
}


auto payment::request::payment_request_update_event::update_with(
        ext::promise<detail::payment_details_update_t>& details_promise)
        -> void
{
    ACCESS_PIMPL(payment_request_update_event);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return !d->is_trusted;},
            u8"Event must be trusted");


    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->wait_for_update;},
            u8"Event is already waiting for an update");

    decltype(auto) request = dom_cast<payment_response*>(d->target)
            ? dom_cast<payment_response*>(d->target)->d_func()->request
            : dom_cast<payment_request*>(d->target);
    ASSERT(request);

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [request] {return request->d_func()->state != detail::state_t::INTERACTIVE;},
            "Request's state must be 'interactive'");

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [request] {return request->d_func()->updating;},
            "Request cannot be updating");

    d->stop_propagation_flag = true;
    d->stop_immediate_propagation_flag = true;
    d->wait_for_update = true;

    auto pmi = dom_cast<payment_method_change_event*>(this) ? dom_cast<payment_method_change_event*>(this)->d_func()->method_name : u8"";
    detail::update_payment_requests_details_algorithm(details_promise, request);
}
