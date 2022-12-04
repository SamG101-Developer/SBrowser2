#pragma once
#ifndef SBROWSER2_HTTP_INTERNALS_HPP
#define SBROWSER2_HTTP_INTERNALS_HPP


#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(url)


namespace fetch::detail
{
    auto is_local_scheme(
            ext::string_view scheme)
            -> ext::boolean;

    auto is_http_scheme(
            ext::string_view scheme)
            -> ext::boolean;

    auto is_fetch_scheme(
            ext::string_view scheme)
            -> ext::boolean;

    auto is_url_local(
            url::detail::url_t& url)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_http_newline_byte(
            T character)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_http_tab_or_space_byte(
            T character)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_http_whitespace_byte(
            T character)
            -> ext::boolean;

    template <ext::string_like T>
    auto collect_http_quoted_string(
            T& input,
            typename T::iterator& position,
            ext::boolean extract_value_flag = false)
            -> T&;
}


#endif //SBROWSER2_HTTP_INTERNALS_HPP
