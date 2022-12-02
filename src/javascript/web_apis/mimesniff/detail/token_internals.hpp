#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_TOKEN_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_TOKEN_INTERNALS_HPP

#include <bit>
#include "ext/boolean.ixx"

namespace mimesniff::detail
{
    auto is_http_token_code_point(
            char32_t code_point)
            -> ext::boolean;

    auto is_http_quoted_string_token_code_point(
            char32_t code_point)
            -> ext::boolean;

    auto is_binary_byte(
            char16_t byte)
            -> ext::boolean;

    auto is_whitespace_byte(
            char16_t byte)
            -> ext::boolean;

    auto is_tag_terminating_byte(
            char16_t byte)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_TOKEN_INTERNALS_HPP
