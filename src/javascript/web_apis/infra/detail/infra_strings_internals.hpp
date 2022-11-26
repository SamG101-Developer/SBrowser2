#pragma once
#ifndef SBROWSER2_STRINGS_HPP
#define SBROWSER2_INFRA_STRINGS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"


namespace infra::detail
{
    template <ext::string_like T>
    auto strip_newlines(
            T& string)
            -> T&;

    template <ext::string_like T>
    auto normalize_newlines(
            T& string)
            -> T&;

    template <ext::string_like T>
    auto strip_leading_ascii_whitespace(
            T& string)
            -> T&;

    template <ext::string_like T>
    auto strip_trailing_ascii_whitespace(
            T& string)
            -> T&;

    template <ext::string_like T>
    auto strip_leading_and_trailing_ascii_whitespace(
            T& string)
            -> T&;

    template <ext::string_like T>
    auto strip_and_collapse_ascii_whitespace(
            T& string)
            -> T&;

    template <ext::string_like T>
    auto collect_ascii_whitespace(
            T& string,
            typename T::iterator& position)
            -> void;

    template <ext::string_like T>
    auto is_ascii_string(
            ext::view_of_t<T> string)
            -> ext::boolean;

    template <ext::string_like T>
    auto collect_code_points_matching(
            T& string,
            typename T::iterator& position,
            auto... code_points)
            -> ext::string;

    template <ext::string_like T>
    auto collect_code_points_not_matching(
            T& string,
            typename T::iterator& position,
            auto... code_points)
            -> ext::string;

    template <ext::string_like T>
    auto is_code_unit_prefix(
            ext::view_of_t<T> potential_prefix,
            ext::view_of_t<T> string)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_code_unit_suffix(
            ext::view_of_t<T> potential_suffix,
            ext::view_of_t<T> string)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_code_unit_less_than(
            ext::view_of_t<T> string0,
            ext::view_of_t<T> string1)
            -> ext::boolean;

    template <ext::string_like T>
    auto code_unit_substring(
            ext::number<size_t> start,
            ext::number<size_t> length,
            ext::view_of_t<T> string)
            -> ext::string;

    template <ext::string_like T>
    auto code_unit_substring_from_start_to_end_within(
            ext::view_of_t<T> string)
            -> ext::string;
}


#endif //SBROWSER2_STRINGS_HPP
