#include "response.hpp"
#include "response_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/general_internals.hpp"
#include "fetch/detail/response_internals.hpp"
#include "fetch/headers.hpp"

#include "infra/detail/code_points_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/contains.hpp>


fetch::response::response(
        detail::body_init_t&& body,
        detail::response_init_t&& init)
{
    INIT_PIMPL(response);
    ACCESS_PIMPL(response);

    d->response = std::make_unique<detail::response_t>();
    d->headers = std::make_unique<headers>(d->response->header_list, detail::header_guard_t::RESPONSE);

    if (!ext::holds_alternative<ext::variant_monostate_t>(std::move(body)))
        detail::initialize_response_object(this, std::move(init), detail::extract(std::move(body)));
}


auto fetch::response::error() -> std::unique_ptr<response>
{
    return detail::create_response_object(detail::create_appropriate_network_error(), detail::header_guard_t::IMMUTABLE);
}


auto fetch::response::redirect(
        ext::string_view url,
        ext::number<ushort> status)
        -> std::unique_ptr<response>
{
    using enum v8_primitive_error_t;
    auto e = js::env::env::current();

    auto parsed_url = url::detail::url_parser(url, **e.cpp.settings()->api_base_url);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&parsed_url] {return !parsed_url.has_value();},
            u8"Error parsing URL", e);

    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [status] {return !ranges::contains(detail::redirect_status, status);},
            u8"Status must be a redirect status", e);

    auto response_object = detail::create_response_object(std::make_unique<detail::response_t>(), detail::header_guard_t::IMMUTABLE);
    response_object->d_func()->response->status = status;

    auto value = infra::detail::isomorphic_encode(url::detail::url_serializer(**parsed_url));
    response_object->d_func()->response->header_list
}
