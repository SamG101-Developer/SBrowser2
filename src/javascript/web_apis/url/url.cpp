#include "url.hpp"
#include "url_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "url/detail/url_internals.hpp"
#include "url/detail/application_internals.hpp"
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
