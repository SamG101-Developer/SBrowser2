#ifndef SBROWSER2_CODE_POINTS_INTERNALS_HPP
#define SBROWSER2_CODE_POINTS_INTERNALS_HPP

#include "ext/boolean.ixx"
#include "ext/string.hpp"

#define DIGITS '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'

namespace infra::detail
{
    enum literals
    {
        LF = 0x000a,
        CR = 0x000d,
        SPACE = 0x0020
    };

    template <ext::char_like T>
    auto is_surrogate(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_scalar(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_non_character(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_code_point(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_tab_or_newline(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_newline(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_whitespace(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_c0_control(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_c0_control_or_space(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_control(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_digit(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_upper_hex_digit(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_lower_hex_digit(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_hex_digit(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_upper_alpha(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_lower_alpha(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_alpha(
            T code_point)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_ascii_alphanumeric(
            T code_point)
            -> ext::boolean;
}

#endif //SBROWSER2_CODE_POINTS_INTERNALS_HPP
