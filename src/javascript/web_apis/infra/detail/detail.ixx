module;
#include "ext/macros/pimpl.hpp"


export module apis.infra.detail;
import apis.infra.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(infra)
{
    enum literals
    {
        LF = 0x000a,
        CR = 0x000d,
        SPACE = 0x0020
    };

    auto is_surrogate(
            code_point_t code_point)
            -> ext::boolean;

    auto is_scalar(
            code_point_t code_point)
            -> ext::boolean;

    auto is_non_character(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_code_point(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_tab_or_newline(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_newline(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_whitespace(
            code_point_t code_point)
            -> ext::boolean;

    auto is_c0_control(
            code_point_t code_point)
            -> ext::boolean;

    auto is_c0_control_or_space(
            code_point_t code_point)
            -> ext::boolean;

    auto is_control(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_digit(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_upper_hex_digit(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_lower_hex_digit(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_hex_digit(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_upper_alpha(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_lower_alpha(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_alpha(
            code_point_t code_point)
            -> ext::boolean;

    auto is_ascii_alphanumeric(
            code_point_t code_point)
            -> ext::boolean;
    
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
