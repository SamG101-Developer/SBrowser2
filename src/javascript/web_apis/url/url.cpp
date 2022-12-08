#include "url.hpp"
#include "_typedefs.hpp"
#include "url_private.hpp"




#include "url/detail/url_internals.hpp"
#include "url/detail/application_internals.hpp"
#include "url/detail/host_internals.hpp"
#include "url/url_search_params.hpp"
#include "url/url_search_params_private.hpp"


url::url::url(ext::string_view url_string, ext::string_view base)
{
    INIT_PIMPL(url);
    using enum v8_primitive_error_t;

    auto parsed_base = detail::basic_url_parser(base);
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&parsed_base] {return !parsed_base.has_value();},
            u8"Error parsing base");

    auto parsed_url = detail::basic_url_parser(url_string);
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&parsed_url] {return !parsed_url.has_value();},
            u8"Error parsing url");

    ACCESS_PIMPL(url);
    d->url = std::move(*parsed_url);
    d->query_object = std::make_unique<url_search_params>(d->url->query);
    d->query_object->d_func()->url = this;
}


auto url::url::get_href() const -> ext::string
{
    ACCESS_PIMPL(const url);
    return detail::url_serializer(*d->url);
}


auto url::url::get_protocol() const -> ext::string
{
    ACCESS_PIMPL(const url);
    return d->url->scheme + char16_t(0x003a);
}


auto url::url::get_username() const -> ext::string
{
    ACCESS_PIMPL(const url);
    return d->url->username;
}


auto url::url::get_password() const -> ext::string
{
    ACCESS_PIMPL(const url);
    return d->url->password;
}


auto url::url::get_host() const -> ext::string
{
    ACCESS_PIMPL(const url);
    return_if (d->url->host.empty()) u"";
    return_if (d->url->port == 0) detail::host_serializer(d->url->host);
    return detail::host_serializer(d->url->host) + char16_t(0x003a) + ext::to_string(d->url->port);
}


auto url::url::get_hostname() const -> ext::string
{
    ACCESS_PIMPL(const url);
    return_if (detail::url_has_opaque_path(*d->url)) u"";
    return detail::host_serializer(d->url->host);
}


auto url::url::set_href(ext::string new_href) -> ext::string
{
    ACCESS_PIMPL(url);
    using enum v8_primitive_error_t;

    auto parsed_url = detail::basic_url_parser(new_href);
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&parsed_url] {return !parsed_url.has_value();},
            u8"Error parsing url");

    d->url = std::move(*parsed_url);
    d->query_object->d_func()->list.clear();

    if (!d->url->query.empty())
        d->query_object->d_func()->list = detail::application_x_www_form_urlencoded_string_parser(d->url->query);
}


auto url::url::set_protocol(ext::string new_protocol) -> ext::string
{
    ACCESS_PIMPL(url);
    return detail::basic_url_parser(std::move(new_protocol) + char16_t(0x003a), u"", nullptr, *d->url, detail::state_override_t::SCHEME_STATE);
}


auto url::url::set_username(ext::string new_username) -> ext::string
{
    ACCESS_PIMPL(url);
    return_if (detail::url_cannot_have_username_password_port(*d->url)) u"";
    return detail::set_username(*d->url, std::move(new_username));
}


auto url::url::set_password(ext::string new_password) -> ext::string
{
    ACCESS_PIMPL(url);
    return_if (detail::url_cannot_have_username_password_port(*d->url)) u"";
    return detail::set_password(*d->url, std::move(new_password));
}


auto url::url::set_host(ext::string new_host) -> ext::string
{
    ACCESS_PIMPL(url);
    return_if (detail::url_has_opaque_path(*d->url)) u"";
    return detail::basic_url_parser(std::move(new_host), u"", nullptr, *d->url, detail::state_override_t::HOST_STATE);
}


auto url::url::set_hostname(ext::string new_hostname) -> ext::string
{
    ACCESS_PIMPL(url);
    return_if (detail::url_has_opaque_path(*d->url)) u"";
    return detail::basic_url_parser(std::move(new_hostname), u"", nullptr, *d->url, detail::state_override_t::HOSTNAME_STATE);
}
