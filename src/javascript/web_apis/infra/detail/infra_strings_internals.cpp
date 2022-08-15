#include "infra_strings_internals.hpp"

#include "ext/functional.hpp"
#include "ext/pair.hpp"
#include "ext/ranges.hpp"

#include "infra/detail/code_points_internals.hpp"

#include <functional>
#include <regex>

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/ends_with.hpp>
#include <range/v3/algorithm/starts_with.hpp>
#include <range/v3/view/zip.hpp>

using namespace std::string_literals;


auto infra::detail::infra_string_internals::strip_newlines(
        ext::string& string)
        -> ext::string&
{
    using namespace code_points_internals::literals;

    // remove all the new line code points
    string = std::regex_replace(string, std::regex("["s + LF + "|" + CR + "]"), "");
    return string;
}


auto infra::detail::infra_string_internals::normalize_newlines(
        ext::string& string)
        -> ext::string&
{
    using namespace code_points_internals::literals;

    // replace all the CRLF code points with a single LF code point, and then replace all the remaining CR code point
    // with a single LF code point
    string = std::regex_replace(string, std::regex("["s + CR + LF + "]"), &LF);
    string = std::regex_replace(string, std::regex("["s + CR      + "]"), &LF);
    return string;
}


auto infra::detail::infra_string_internals::strip_leading_and_trailing_ascii_whitespace(
        ext::string& string)
        -> ext::string&
{
    // remove all the leading and trailing space code points
    string = std::regex_replace(string, std::regex("^\\s+|\\s+$"), "");
    return string;
}


auto infra::detail::infra_string_internals::strip_and_collapse_ascii_whitespace(
        ext::string& string)
        -> ext::string&
{
    // remove all the leading and trailing space code points, and then replace all the double space code point with
    // single space code points
    string = std::regex_replace(string, std::regex("[' ']{2,}"  ), " ");
    string = strip_leading_and_trailing_ascii_whitespace(string);
    return string;
}


auto infra::detail::infra_string_internals::is_ascii_string(
        ext::string_view string)
        -> ext::boolean
{
    // a string is as ascii string if all of its code points are ascii code points (not unicode, although a unicode
    // string count pass this test)
    return ranges::all_of(string, ext::bind_front(code_points_internals::is_ascii_code_point));
}


auto infra::detail::infra_string_internals::is_code_unit_prefix(
        ext::string_view potential_prefix,
        ext::string_view string)
        -> ext::boolean
{
    return ranges::starts_with(string, potential_prefix);
}


auto infra::detail::infra_string_internals::is_code_unit_suffix(
        ext::string_view potential_suffix,
        ext::string_view string)
        -> ext::boolean
{
    return ranges::ends_with(string, potential_suffix);
}


auto infra::detail::infra_string_internals::is_code_unit_less_than(
        ext::string_view string0,
        ext::string_view string1)
        -> ext::boolean
{
    if (is_code_unit_prefix(string0, string1)) return false;
    if (is_code_unit_prefix(string1, string0)) return true;

    for (auto&& pair: ranges::views::zip(string0, string1))
        return_if (pair.first != pair.second) pair.first < pair.second;
    return false;
}
