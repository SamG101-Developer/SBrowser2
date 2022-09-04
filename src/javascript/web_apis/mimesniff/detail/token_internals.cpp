#include "token_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/iota.hpp>


auto mimesniff::detail::is_http_token_code_point(
        char32_t code_point)
        -> ext::boolean
{
    auto http_token_code_points = {
            0x0021, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x002a, 0x002b, 0x002d, 0x002e,
            0x005e, 0x005f, 0x0060, 0x007c, 0x007e};

    return ranges::contains(http_token_code_points, code_point);
}


auto mimesniff::detail::is_http_quoted_string_token_code_point(
        char32_t code_point)
        -> ext::boolean
{
    auto http_quoted_string_toke_code_point = ranges::views::concat(
            ranges::views::closed_iota(0x0020, 0x007e),
            ranges::views::closed_iota(0x0080, 0x00ff));

    return code_point == 0x0009 || ranges::contains(http_quoted_string_toke_code_point, code_point);
}


auto mimesniff::detail::is_binary_byte(
        char16_t byte)
        -> ext::boolean
{
    auto binary_bytes = ranges::views::concat(
            ranges::views::closed_iota(0x00, 0x08),
            ranges::views::closed_iota(0x0e, 0x1a),
            ranges::views::closed_iota(0x1c, 0x1f));

    return byte == 0x0b || ranges::contains(binary_bytes, byte);
}


auto mimesniff::detail::is_whitespace_byte(
        char16_t byte)
        -> ext::boolean
{
    auto whitespace_bytes = {0x09, 0x0a, 0x0c, 0x0d, 0x20};
    return ranges::contains(whitespace_bytes, byte);
}


auto mimesniff::detail::is_tag_terminating_byte(
        char16_t byte)
        -> ext::boolean
{
    auto tag_terminating_bytes = {0x20, 0x3e};
    return ranges::contains(tag_terminating_bytes, byte);
}
