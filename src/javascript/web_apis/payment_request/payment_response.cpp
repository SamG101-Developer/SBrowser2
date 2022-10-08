#include "payment_response.hpp"
#include "payment_response_private.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"
#include "dom/other/dom_exception.hpp"


auto payment::request::payment_response::retry(
        detail::payment_validation_errors_t&& error_fields)
        -> ext::promise<void>
{
    ACCESS_PIMPL(payment_response);

    decltype(auto) request = d->request;
    JS_REALM_GET_RELEVANT(request);

    decltype(auto) document = v8pp::from_v8<dom::nodes::window*>(request_relevant_global_object)->d_func()->document;

    auto promise = ext::promise<void>{};
    return_if (!dom::detail::is_document_fully_active(document)) promise.reject(dom::other::dom_exception);
}
