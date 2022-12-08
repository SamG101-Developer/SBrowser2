#include "headers.hpp"
#include "headers_private.hpp"




#include "fetch/_typedefs.hpp"
#include "fetch/detail/header_internals.hpp"


fetch::headers::headers(detail::headers_t&& headers)
{
    INIT_PIMPL(headers);

    ACCESS_PIMPL(headers);
    d->headers_guard = detail::header_guard_t::NONE;
    d->headers_list = std::move(headers);
}


auto fetch::headers::append(
        detail::header_name_t&& name,
        detail::header_value_t&& value)
        -> void
{
    ACCESS_PIMPL(headers);
    using enum v8_primitive_error_t;
    detail::normalize(value);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&name, &value] {return !detail::is_header_name(name) || !detail::is_header_value(value);},
            u8"Name and value must be a valid header name and value");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {d->headers_guard == detail::header_guard_t::IMMUTABLE;},
            u8"Cannot modify a header whose guard is 'immutable'");

    return_if (
            d->headers_guard == detail::header_guard_t::REQUEST_NO_CORS
            && !detail::is_no_cors_safelisted_request_header({name, detail::get_header_value(name, d->headers_list) + char8_t(0x2d) + char8_t(0x20) + value}));

    return_if (
            d->headers_guard == detail::header_guard_t::RESPONSE
            && detail::is_forbidden_response_header_name(name));

    detail::append_header({std::move(name), std::move(value)}, d->headers_list);

    if (d->headers_guard == detail::header_guard_t::REQUEST_NO_CORS)
        detail::remove_privileged_no_cors_request_headers(d->headers_list);
}


auto fetch::headers::delete_(
        ext::u8string_view name)
        -> void
{
    ACCESS_PIMPL(headers);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&name] {return !detail::is_header_name(name);},
            u8"Name must be a valid header name");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [d] {d->headers_guard == detail::header_guard_t::IMMUTABLE;},
            u8"Cannot modify a header whose guard is 'immutable'");

    return_if (
            d->headers_guard == detail::header_guard_t::REQUEST
            && detail::is_forbidden_request_header({name, ""}));

    return_if (
            d->headers_guard == detail::header_guard_t::REQUEST_NO_CORS
            && !detail::is_no_cors_safelisted_request_header_name(name)
            && !detail::is_privileged_no_cors_request_header_name(name));

    return_if (
            d->headers_guard == detail::header_guard_t::RESPONSE
            && detail::is_forbidden_response_header_name(name));

    return_if (!detail::header_list_contains_header(d->headers_list, name));
    detail::delete_header(name, d->headers_list);

    if (d->headers_guard == detail::header_guard_t::REQUEST_NO_CORS)
        detail::remove_privileged_no_cors_request_headers(d->headers_list);
}


auto fetch::headers::get(
        ext::u8string_view name)
        -> detail::header_value_t
{
    ACCESS_PIMPL(headers);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&name] {return !detail::is_header_name(name);},
            u8"Name must be a valid header name");

    return detail::get_header_value(name, d->headers_list);
}


auto fetch::headers::has(
        ext::u8string_view name)
        -> ext::boolean
{
    ACCESS_PIMPL(headers);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&name] {return !detail::is_header_name(name);},
            u8"Name must be a valid header name");

    return detail::header_list_contains_header(name, d->headers_list);
}


auto fetch::headers::set(
        detail::header_name_t&& name,
        detail::header_value_t&& value)
        -> void
{
    ACCESS_PIMPL(headers);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&name] {return !detail::is_header_name(name);},
            u8"Name must be a valid header name");

    // TODO (doable, cba rn)
}


auto fetch::headers::operator[](const detail::header_name_t& key) -> detail::header_value_t&
{
    ACCESS_PIMPL(headers);
    return detail::get_header_value(key, detail::sort_and_combine(d->headers_list));
}


auto fetch::headers::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .inherit<ext::map_like<detail::header_name_t , detail::header_name_t>>()
        .ctor<detail::headers_t&&>()
        .function("append", &headers::append)
        .function("delete", &headers::delete_)
        .function("get", &headers::get)
        .function("has", &headers::has)
        .function("set", &headers::set)
        .auto_wrap_objects();
}
