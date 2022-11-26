#include "code_points_internals.hpp"

#include <initializer_list>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/iota.hpp>


template <ext::char_like T>
auto infra::detail::is_surrogate(T code_point) -> ext::boolean
{
    // a surrogate code point is half a unicode code point, that is combined with another surrogate code point, to
    // represent a single unicode character
    return ranges::contains(ranges::views::closed_iota(0xd800, 0xdfff), code_point);
}


template <ext::char_like T>
auto infra::detail::is_scalar(T code_point) -> ext::boolean
{
    // a scalar code point is a single unicode code point, that represents a single unicode character; it is every code
    // point that isn't a surrogate code point
    return !is_surrogate(code_point);
}


template <ext::char_like T>
auto infra::detail::is_non_character(T code_point) -> ext::boolean // TODO : format this method
{
    // a non character code point is a unicode code point that doesn't have amy way to be displayed on a screen and is
    // therefore not useful for string literals of information
    return ranges::contains(ranges::views::closed_iota(0xfdd0, 0xfdef), code_point) || ranges::contains(std::initializer_list<T>{
        0xfffe, 0xffff, 0x1fffe, 0x1ffff, 0x2fffe, 0x2ffff, 0x3fffe, 0x3ffff, 0x4fffe, 0x4ffff, 0x5fffe, 0x5ffff,
        0x6fffe, 0x6ffff, 0x7fffe, 0x7ffff, 0x8fffe, 0x8ffff, 0x9fffe, 0x9ffff, 0xafffe, 0xaffff, 0xbfffe, 0xbffff,
        0xcfffe, 0xcffff, 0xdfffe, 0xdffff, 0xefffe, 0xeffff, 0xffffe, 0xfffff, 0x10fffe, 0x10ffff}, code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_code_point(T code_point) -> ext::boolean
{
    // an ascii code point is a code point that is in the range of all ascii characters, which is from 0 through to 127
    // inclusive (0x007f)
    return ranges::contains(ranges::views::closed_iota(0x0000, 0x007f), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_tab_or_newline(T code_point) -> ext::boolean
{
    return code_point == 0x0009 || is_ascii_newline(code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_newline(T code_point) -> ext::boolean
{
    // an ascii tab or newline is a code point that is a TAB, LF or CR character (tab, line feed or carriage return), as
    // these all produce tabb-looking characters
    return ranges::contains(std::initializer_list<T>{0x000A, 0x000D}, code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_whitespace(T code_point) -> ext::boolean
{
    // an ascii whitespace code point is a code point that is a TAB, LF, FF, CR or SPACE (tab, line feed, form feed,
    // carriage return or normal space), as these all produce space-looking characters
    return ranges::contains(std::initializer_list<T>{0x0009, 0x000a, 0x000c, 0x000d, 0x0020}, code_point);
}


template <ext::char_like T>
auto infra::detail::is_c0_control(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0000, 0x001f), code_point);
}


template <ext::char_like T>
auto infra::detail::is_c0_control_or_space(T code_point) -> ext::boolean
{
    return is_c0_control(code_point) || is_ascii_whitespace(code_point);
}


template <ext::char_like T>
auto infra::detail::is_control(T code_point) -> ext::boolean
{
    return is_c0_control(code_point) || ranges::contains(ranges::views::closed_iota(0x007f, 0x009f), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_digit(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0030, 0x0039), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_upper_hex_digit(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0041, 0x0046), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_lower_hex_digit(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0061, 0x007a), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_hex_digit(T code_point) -> ext::boolean
{
    return is_ascii_lower_hex_digit(code_point) || is_ascii_upper_hex_digit(code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_upper_alpha(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0041, 0x005a), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_lower_alpha(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0061, 0x007a), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_alpha(T code_point) -> ext::boolean
{
    return ranges::contains(ranges::views::closed_iota(0x0041, 0x005a), code_point);
}


template <ext::char_like T>
auto infra::detail::is_ascii_alphanumeric(T code_point) -> ext::boolean
{
    return is_ascii_digit(code_point) || is_ascii_alpha(code_point);
}
