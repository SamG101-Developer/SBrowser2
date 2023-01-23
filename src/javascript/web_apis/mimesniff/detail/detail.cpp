module;
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/iota.hpp>


module apis.mimesniff.detail;
import apis.mimesniff.types;

import ext.core;


template <ext::char_like T>
auto mimesniff::detail::is_http_token_code_point(T code_point) -> ext::boolean
{
    auto code_points = {0x0021, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x002a, 0x002b, 0x002d, 0x002e, 0x005e, 0x005f, 0x0060, 0x007c, 0x007e};
    return ranges::contains(code_points, code_point);
}


template <ext::char_like T>
auto mimesniff::detail::is_http_quoted_string_token_code_point(T code_point) -> ext::boolean
{
    auto code_points = ranges::views::concat(ranges::views::closed_iota(0x0020, 0x007e), ranges::views::closed_iota(0x0080, 0x00ff));
    return code_point == 0x0009 || ranges::contains(code_points, code_point);
}


template <ext::char_like T>
auto mimesniff::detail::is_binary_byte(T byte) -> ext::boolean
{
    auto bytes = ranges::views::concat(ranges::views::closed_iota(0x00, 0x08), ranges::views::closed_iota(0x0e, 0x1a), ranges::views::closed_iota(0x1c, 0x1f));
    return byte == 0x0b || ranges::contains(bytes, byte);
}


template <ext::char_like T>
auto mimesniff::detail::is_whitespace_byte(T byte) -> ext::boolean
{
    auto bytes = {0x09, 0x0a, 0x0c, 0x0d, 0x20};
    return ranges::contains(bytes, byte);
}


template <ext::char_like T>
auto mimesniff::detail::is_tag_terminating_byte(T byte) -> ext::boolean
{
    auto bytes = {0x20, 0x3e};
    return ranges::contains(bytes, byte);
}


auto mimesniff::detail::essence(const detail::mime_type_t& mime_type) -> ext::string
{
    return mime_type.type + char16_t(0x002f) + mime_type.sub_type;
}


auto mimesniff::detail::mime_type_supported_by_user_agent(const mime_type_t& mime_type) -> ext::boolean
{
    // TODO
}
