#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_HOST_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_HOST_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(url)


namespace url::detail
{
    auto is_host_opaque(
            domain_t&& host)
            -> ext::boolean;

    auto is_empty_host(
            domain_t&& host)
            -> ext::boolean;

    auto is_forbidden_host_code_point(
            wchar_t code_point)
            -> ext::boolean;

    auto host_public_suffix(
            domain_t&& host)
            -> ext::string;

    auto host_registerable_domain(
            domain_t&& host)
            -> ext::string;

    auto domain_to_ascii(
            domain_t&& domain,
            ext::boolean be_strict)
            -> ext::optional<ext::string>;

    auto domain_to_unicode(
            domain_t&& domain)
            -> ext::optional<ext::string>;

    auto is_valid_host_string(
            domain_t&& host)
            -> ext::boolean;

    auto is_valid_domain_string(
            domain_t&& domain)
            -> ext::boolean;

    auto is_valid_ipv4_address_string(
            domain_t&& domain)
            -> ext::boolean;

    auto is_valid_ipv6_address_string(
            domain_t&& domain)
            -> ext::boolean;

    auto is_valid_opaque_host_string(
            domain_t&& domain)
            -> ext::boolean;

    auto host_parser(
            domain_t&& input,
            ext::boolean is_not_special = false)
            -> ext::optional<domain_t>;

    auto ipv4_parser(
            domain_t&& input)
            -> ext::optional<ext::number<char>>;

    auto ipv6_parser(
            domain_t&& input)
            -> ext::optional<ext::number<char>>;

    auto ipv4_number_parser(
            domain_t&& input)
            -> ext::optional<ext::number<char>>;

    auto opaque_host_parser(
            domain_t&& input)
            -> ext::optional<domain_t>;

    auto ends_in_number_checker(
            ext::string&& input)
            -> ext::boolean;

    auto host_serializer(
            ext::string_view host)
            -> domain_t;

    auto ipv4_serializer(
            ext::string_view address)
            -> domain_t;

    auto ipv6_serializer(
            ext::string_view address)
            -> domain_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_HOST_INTERNALS_HPP
