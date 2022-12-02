#include "infra_strings_internals.hpp"

#include "ext/functional.ixx"
#include "ext/pair.ixx"
#include "ext/ranges.hpp"
#include "ext/regex.ixx"

#include "infra/detail/code_points_internals.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/ends_with.hpp>
#include <range/v3/algorithm/starts_with.hpp>
#include <range/v3/view/zip.hpp>


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
    if (is_code_unit_prefix(string0, string1)) return false;
    if (is_code_unit_prefix(string1, string0)) return true;

    for (auto&& pair: ranges::views::zip(string0, string1))
        return_if (pair.first != pair.second) pair.first < pair.second;
    return false;
}
