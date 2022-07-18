#include "miscellaneous_internals.hpp"

#include "fetch/detail/request_internals.hpp"


auto html::detail::miscellaneous_internals::create_potential_cors_request(
        url::url_object& url,
        fetch::detail::request_internals::destination_t destination,
        fetch::detail::request_internals::mode_t cors_attribute_state,
        ext::boolean&& same_origin_fallback_flag)
        -> fetch::detail::request_internals::internal_request
{
    using mode_t = fetch::detail::request_internals::mode_t;
    using credentials_t = fetch::detail::request_internals::credentials_t;

    auto credentials_mode = cors_attribute_state == mode_t::ANONYMOUS ? credentials_t::INCLUDE : credentials_t::SAME_ORIGIN;

    return fetch::detail::request_internals::internal_request
    {
        .url = url,
        .destination = destination,
        .mode = cors_attribute_state,
        .credentials_mode = credentials_mode,
        .use_url_credentials_flag = ext::boolean::TRUE()
    };
}
