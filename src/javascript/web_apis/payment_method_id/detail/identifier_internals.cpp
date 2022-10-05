#include "identifier_internals.hpp"

#include "url/detail/url_internals.hpp"


auto payment::detail::validate_payment_method_identifier(
        ext::string_view pmi)
        -> ext::boolean
{
    decltype(auto) url = url::detail::basic_url_parser(pmi);
    return !url.has_value()
            ? validate_standardized_payment_method_identifier(pmi)
            : validate_url_based_payment_method_identifier(url);
}


auto payment::detail::validate_url_based_payment_method_identifier(
        const url::detail::url_t& url)
        -> ext::boolean
{
    return_if (url.scheme != "https") false;
    return_if (!url.username.empty() || !url.password.empty()) false;
    return true;
}
