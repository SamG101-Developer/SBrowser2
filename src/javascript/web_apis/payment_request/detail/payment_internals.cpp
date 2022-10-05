#include "payment_internals.hpp"

#include "javascript//environment/realms_2.hpp"

#include "html/detail/context_internals.hpp"


auto payment::detail::payment_relevant_browsing_context(
        request::payment_request* request)
        -> html::detail::browsing_context_t&
{
    JS_REALM_GET_RELEVANT(request);
    decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(request_relevant_agent, request_relevant_global_object);
    decltype(auto) context = *window->d_func()->document->d_func()->browsing_context;
    return context->top_level_context();
}
