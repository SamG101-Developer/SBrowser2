#pragma once
#ifndef SBROWSER2_STRINGS_HPP
#define SBROWSER2_INFRA_STRINGS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"


namespace infra::detail
{
    auto strip_newlines(
            ext::string& string)
            -> ext::string&;

    auto normalize_newlines(
            ext::string& string)
            -> ext::string&;

    auto strip_leading_ascii_whitespace(
            ext::string& string)
            -> ext::string&;

    auto strip_trailing_ascii_whitespace(
            ext::string& string)
            -> ext::string&;

    auto strip_leading_and_trailing_ascii_whitespace(
            ext::string& string)
            -> ext::string&;

    auto strip_and_collapse_ascii_whitespace(
            ext::string& string)
            -> ext::string&;

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
            auto... code_points)
            -> ext::string;

    auto collect_code_points_not_matching(
            ext::string& string,
            ext::string::iterator& position,
            auto... code_points)
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
}


#endif //SBROWSER2_STRINGS_HPP
