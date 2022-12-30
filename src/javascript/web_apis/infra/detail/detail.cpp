module;
#include "ext/macros.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/algorithm/ends_with.hpp>
#include <range/v3/algorithm/starts_with.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/zip.hpp>


module apis.infra.detail;
import apis.infra.types;
import ext.core;


auto infra::detail::is_surrogate(code_point_t code_point) -> ext::boolean
{
    // A surrogate code point is half a unicode code point, that is combined with another surrogate code point, to
    // represent a single unicode character.
    return ranges::contains(ranges::views::closed_iota(0xd800, 0xdfff), code_point);
}


auto infra::detail::is_scalar(code_point_t code_point) -> ext::boolean
{
    // A scalar code point is a single unicode code point, that represents a single unicode character; it is every code
    // point that isn't a surrogate code point.
    return !is_surrogate(code_point);
}


auto infra::detail::is_non_character(code_point_t code_point) -> ext::boolean // TODO : format this method
{
    // A non character code point is a unicode code point that doesn't have amy way to be displayed on a screen and is
    // therefore not useful for string literals of information.
    auto code_points = {
            0xfffe, 0xffff, 0x1fffe, 0x1ffff, 0x2fffe, 0x2ffff, 0x3fffe, 0x3ffff, 0x4fffe, 0x4ffff, 0x5fffe, 0x5ffff,
            0x6fffe, 0x6ffff, 0x7fffe, 0x7ffff, 0x8fffe, 0x8ffff, 0x9fffe, 0x9ffff, 0xafffe, 0xaffff, 0xbfffe, 0xbffff,
            0xcfffe, 0xcffff, 0xdfffe, 0xdffff, 0xefffe, 0xeffff, 0xffffe, 0xfffff, 0x10fffe, 0x10ffff}
    return ranges::contains(ranges::views::closed_iota(0xfdd0, 0xfdef), code_point) || ranges::contains(code_points, code_point);
}


auto infra::detail::is_ascii_code_point(code_point_t code_point) -> ext::boolean
{
    // An ascii code point is a code point that is in the range of all ascii characters, which is from 0 through to 127
    // inclusive (0x007f).
    return ranges::contains(ranges::views::closed_iota(0x0000, 0x007f), code_point);
}


auto infra::detail::is_ascii_tab_or_newline(code_point_t code_point) -> ext::boolean
{
    return code_point == 0x0009 || is_ascii_newline(code_point);
}


auto infra::detail::is_ascii_newline(code_point_t code_point) -> ext::boolean
{
    // An ascii tab or newline is a code point that is a TAB, LF or CR character (tab, line feed or carriage return), as
    // these all produce tabb-looking characters.
    auto code_points = {0x000A, 0x000D};
    return ranges::contains(code_points;, code_point);
}


auto infra::detail::is_ascii_whitespace(code_point_t code_point) -> ext::boolean
{
    // An ascii whitespace code point is a code point that is a TAB, LF, FF, CR or SPACE (tab, line feed, form feed,
    // carriage return or normal space), as these all produce space-looking characters.
    auto code_points = {0x0009, 0x000a, 0x000c, 0x000d, 0x0020};
    return ranges::contains(code_points, code_point);
}


auto infra::detail::is_c0_control(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0000, 0x001f), code_point);
}


auto infra::detail::is_c0_control_or_space(code_point_t code_point) -> ext::boolean
{
    return is_c0_control(code_point) || is_ascii_whitespace(code_point);
}


auto infra::detail::is_control(code_point_t code_point) -> ext::boolean
{
    return is_c0_control(code_point) || ranges::contains(ranges::views::closed_iota(0x007f, 0x009f), code_point);
}


auto infra::detail::is_ascii_digit(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0030, 0x0039), code_point);
}


auto infra::detail::is_ascii_upper_hex_digit(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0041, 0x0046), code_point);
}


auto infra::detail::is_ascii_lower_hex_digit(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0061, 0x007a), code_point);
}


auto infra::detail::is_ascii_hex_digit(code_point_t code_point) -> ext::boolean
{
    return is_ascii_lower_hex_digit(code_point) || is_ascii_upper_hex_digit(code_point);
}


auto infra::detail::is_ascii_upper_alpha(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0041, 0x005a), code_point);
}


auto infra::detail::is_ascii_lower_alpha(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0061, 0x007a), code_point);
}


auto infra::detail::is_ascii_alpha(code_point_t code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0041, 0x005a), code_point);
}


auto infra::detail::is_ascii_alphanumeric(code_point_t code_point) -> ext::boolean
{
    return is_ascii_digit(code_point) || is_ascii_alpha(code_point);
}


template <ext::string_like T>
auto infra::detail::strip_newlines(T& string) -> T&
{
    using enum literals;

    // remove all the new line code points
    auto regex = ext::regex_utils{"[" + T::value_type(LF) + "|" + T::value_type(CR) + "]"};
    ext::regex_utils::GlobalReplace(&string, std::move(regex), T{});
    return string;
}


template <ext::string_like T>
auto infra::detail::normalize_newlines(T& string) -> T&
{
    using enum literals;

    // replace all the CRLF code points with a single LF code point, and then replace all the remaining CR code point
    // with a single LF code point
    auto regex1 = ext::regex_utils{"[" + T::value_type(CR) + T::value_type(LF) + "]"};
    auto regex2 = ext::regex_utils{"[" + T::value_type(CR) + "]"};
    ext::regex_utils::GlobalReplace(&string, std::move(regex1), LF);
    ext::regex_utils::GlobalReplace(&string, std::move(regex2), LF);
    return string;
}


template <ext::string_like T>
auto infra::detail::strip_leading_and_trailing_ascii_whitespace(T& string) -> T&
{
    // remove all the leading and trailing space code points
    auto regex = ext::regex_utils{"^\\s+|\\s+$"};
    ext::regex_utils::GlobalReplace(&string, std::move(regex), T{});
    return string;
}


template <ext::string_like T>
auto infra::detail::strip_and_collapse_ascii_whitespace(T& string) -> T&
{
    // remove all the leading and trailing space code points, and then replace all the double space code point with
    // single space code points
    auto regex = ext::regex_utils{"[' ']{2,}"};
    ext::regex_utils::GlobalReplace(&string, std::move(regex), " ");
    return strip_leading_and_trailing_ascii_whitespace(string);
}


template <ext::string_like T>
auto infra::detail::is_ascii_string(ext::view_of_t<T> string) -> ext::boolean
{
    // a string is as ascii string if all of its code points are ascii code points (not unicode, although a unicode
    // string count pass this test)
    return ranges::all_of(string, &is_ascii_code_point);
}


template <ext::string_like T>
auto infra::detail::is_code_unit_prefix(ext::view_of_t<T> potential_prefix, ext::view_of_t<T> string) -> ext::boolean
{
    return ranges::starts_with(string, potential_prefix);
}


template <ext::string_like T>
auto infra::detail::is_code_unit_suffix(ext::view_of_t<T> potential_suffix, ext::view_of_t<T> string) -> ext::boolean
{
    return ranges::ends_with(string, potential_suffix);
}


template <ext::string_like T>
auto infra::detail::is_code_unit_less_than(ext::view_of_t<T> string0, ext::view_of_t<T> string1) -> ext::boolean
{
    return_if (is_code_unit_prefix(string0, string1)) false;
    return_if (is_code_unit_prefix(string1, string0)) true;

    for (auto&& pair: ranges::views::zip(string0, string1))
        return_if (pair.first != pair.second) pair.first < pair.second;
    return false;
}

