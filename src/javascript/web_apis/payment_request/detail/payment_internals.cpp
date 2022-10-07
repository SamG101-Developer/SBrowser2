#include "payment_internals.hpp"

#include "ext/regex.hpp"
#include "javascript/environment/realms_2.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"
#include "dom/nodes/window.hpp"

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


auto payment::detail::is_valid_decimal_monetary_value(
        ext::string_view string)
        -> ext::boolean
{
    using namespace ext::literals;
    auto match_info = "^-?[0-9]+(\\.[0-9]+)?$"_ctre.match(string);
    return static_cast<bool>(match_info);
}


auto payment::detail::check_and_canonicalize_amount(
        detail::payment_currency_amount_t& amount)
        -> void
{
    // TODO : JS Check

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [validation = is_valid_decimal_monetary_value(amount.at("value").to<ext::string>())] {return !validation;},
            "Amount's value must be a valid decimal monetary value");
}
