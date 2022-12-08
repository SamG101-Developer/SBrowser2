#include "payment_response.hpp"
#include "payment_response_private.hpp"

#include "javascript/environment/realms_2.hpp"

#include INCLUDE_INNER_TYPES(dom)






#include "html/detail/context_internals.hpp"

#include "payment_request/detail/payment_internals.hpp"
#include "payment_request/payment_request.hpp"
#include "payment_request/payment_request_private.hpp"


auto payment::request::payment_response::complete(
        detail::payment_complete_t result,
        detail::payment_complete_details_t&& details)
        -> ext::promise<void>
{
    ACCESS_PIMPL(payment_response);
    using enum dom::detail::dom_exception_error_t;

    auto promise = ext::promise<void>{};
    return_if (d->complete) promise.reject(dom::other::dom_exception{u8"Cannot complete an already completed response", INVALID_STATE_ERR});
    return_if (d->retry_promise.ahs_Value()) promise.reject(dom::other::dom_exception{u8"Cannot complete a response that has a retry promise", INVALID_STATE_ERR});

    JS_EXCEPTION_HANDLER;
    auto serialized_data = details[u8"data"].to<ext::string>();
    if (JS_EXCEPTION_HAS_THROWN)
        return promise.reject(JS_EXCEPTION);

    // TODO : methodName

    d->complete = true;

    GO [&promise]
    {
        // TODO
    };

    return promise;
}


auto payment::request::payment_response::retry(
        detail::payment_validation_errors_t&& error_fields)
        -> ext::promise<void>
{
    ACCESS_PIMPL(payment_response);
    using enum dom::detail::dom_exception_error_t;
    using namespace ext::literals;

    decltype(auto) request = d->request;
    auto e = js::env::env::relevant(request);

    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document;

    auto promise = ext::promise<void>{};
    return_if (!dom::detail::is_document_fully_active(document)) promise.reject(dom::other::dom_exception{u8"Document must be fully active", ABORT_ERR});
    return_if (d->complete) promise.reject(dom::other::dom_exception{u8"Response already completed", INVALID_STATE_ERR}); // TODO : check how promise is null (optional?)
    return_if (d->retry_promise.has_value()) promise.reject(dom::other::dom_exception{u8"Response has a retry promise", INVALID_STATE_ERR});

    request->d_func()->state = detail::state_t::INTERACTIVE;
    d->retry_promise = ext::promise<void>{};

    if (!error_fields.empty())
    {
        JS_EXCEPTION_HANDLER;
        // TODO if (error_fields.contains(u8"paymentMethod"))
        detail::payment_relevant_browsing_context(request).payment_request_is_showing = false;

        if (JS_EXCEPTION_HAS_THROWN)
        {
            d->retry_promise->reject(JS_EXCEPTION);
            detail::payment_relevant_browsing_context(request).payment_request_is_showing = false; // TODO : correct context?
            return;
        }

        // TODO
    }

    // TODO
}
