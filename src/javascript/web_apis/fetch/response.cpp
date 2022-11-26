#include "response.hpp"
#include "environment/realms.hpp"
#include "response_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/general_internals.hpp"
#include "fetch/detail/response_internals.hpp"
#include "fetch/headers.hpp"
#include "fetch/headers_private.hpp"

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
    response_object->d_func()->response->header_list;
}


auto fetch::response::clone() -> std::unique_ptr<response>
{
    ACCESS_PIMPL(const response);
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this); // TODO : env

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this] {return detail::is_unusable(this);},
            u8"Cannot clone an unusable Response", e);

    auto cloned_response = detail::clone_response(*d->response);
    auto cloned_response_object = detail::create_response_object(std::move(cloned_response), d->headers->d_func()->headers_guard);
    return std::move(cloned_response_object);
}


auto fetch::response::get_type() const -> detail::response_type_t
{
    ACCESS_PIMPL(const response);
    return d->response->type;
}


auto fetch::response::get_url() const -> ext::string
{
    ACCESS_PIMPL(const response);
    return d->response->url ? url::detail::url_serializer(**d->response->url) : u"";
}


auto fetch::response::get_redirected() const -> ext::boolean
{
    ACCESS_PIMPL(const response);
    return d->response->url_list.size() > 1;
}


auto fetch::response::get_status() const -> ext::number<ushort>
{
    ACCESS_PIMPL(const response);
    return d->response->status;
}


auto fetch::response::get_ok() const -> ext::boolean
{
    ACCESS_PIMPL(const response);
    return ranges::contains(detail::ok_status, d->response->status);
}


auto fetch::response::get_status_text() const -> ext::u8string_view
{
    ACCESS_PIMPL(const response);
    return d->response->status_message;
}


auto fetch::response::get_headers() const -> headers*
{
    ACCESS_PIMPL(const response);
    return d->headers.get();
}


auto fetch::response::_to_v8(js::env::module_t E, v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .inherit<mixins::body>()
        .function("error", &response::error)
        .function("redirect", &response::redirect)
        .function("json", &response::json)
        .function("clone", &response::clone)
        .property("type", &response::get_type)
        .property("URL", &response::get_url)
        .property("redirected", &response::get_redirected)
        .property("status", &response::get_status)
        .property("ok", &response::get_ok)
        .property("statusText", &response::get_status_text)
        .property("headers", &response::get_headers);

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
