#pragma once
#ifndef SBROWSER2_HTTP_INTERNALS_HPP
#define SBROWSER2_HTTP_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(url)


namespace fetch::detail
{
    auto is_url_local(
            url::detail::url_t& url)
            -> ext::boolean;

    auto is_http_newline_byte(
            char8_t character)
            -> ext::boolean;

    auto is_http_tab_or_space_byte(
            char8_t character)
            -> ext::boolean;

    auto is_http_whitespace_byte(
            char8_t character)
            -> ext::boolean;

    auto collect_http_quoted_string(
            ext::string& input,
            ext::string::iterator& position,
            ext::boolean extract_value_flag = false)
            -> ext::string;
}


#endif //SBROWSER2_HTTP_INTERNALS_HPP
