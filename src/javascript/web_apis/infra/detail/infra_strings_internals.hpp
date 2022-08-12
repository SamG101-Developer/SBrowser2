#pragma once
#ifndef SBROWSER2_STRINGS_HPP
#define SBROWSER2_INFRA_STRINGS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"

#include <range/v3/algorithm/starts_with.hpp>
#include <range/v3/view/zip.hpp>

namespace infra::detail::infra_string_internals
{
    auto strip_newlines(
            ext::string& string)
            -> ext::string;

    auto normalize_newlines(
            ext::string& string)
            -> ext::string;

    auto strip_leading_and_trailing_ascii_whitespace(
            ext::string& string)
            -> ext::string;

    auto strip_and_collapse_ascii_whitespace(
            ext::string& string)
            -> ext::string;

    auto collect_ascii_whitespace(
            ext::string& string,
            ext::string::iterator& position)
            -> void;

    auto is_ascii_string(
            ext::string_view string)
            -> ext::boolean;

    auto collect_code_points_matching(
            ext::string& string,
            ext::string::iterator& position,
            type_is<char> auto&&... code_points)
            -> ext::string;

    auto collect_code_points_not_matching(
            ext::string& string,
            ext::string::iterator& position,
            type_is<char> auto&&... code_points)
            -> ext::string;

    auto is_code_unit_prefix(
            ext::string_view potential_prefix,
            ext::string_view string)
            -> ext::boolean;

    auto is_code_unit_suffix(
            ext::string_view potential_suffix,
            ext::string_view string)
            -> ext::boolean;

    auto is_code_unit_substring(
            ext::string_view potential_substring,
            ext::string_view string)
            -> ext::boolean;

    auto is_code_unit_less_than(
            ext::string_view string0,
            ext::string_view string1)
            -> ext::boolean;

    struct byte_less_than_fn
    {
        constexpr auto operator()(ext::string_view a, ext::string_view b) const -> ext::boolean
        {
            return_if (ranges::starts_with(a, b)) false;
            return_if (ranges::starts_with(b, a)) true;

            for (const auto& pair: ranges::views::zip(a, b))
            {
                return_if (pair.first != pair.second) char(pair.first) < char(pair.second);
            }
        }
    };

    constexpr byte_less_than_fn byte_less_than;
}


#endif //SBROWSER2_STRINGS_HPP
