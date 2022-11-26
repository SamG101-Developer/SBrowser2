#ifndef SBROWSER2_CODE_POINTS_INTERNALS_HPP
#define SBROWSER2_CODE_POINTS_INTERNALS_HPP

#include "ext/boolean.hpp"
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

    template <ext::string_like T>
    auto is_surrogate(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_scalar(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_non_character(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_code_point(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_tab_or_newline(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_newline(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_whitespace(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_c0_control(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_c0_control_or_space(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_control(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_digit(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_upper_hex_digit(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_lower_hex_digit(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_hex_digit(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_upper_alpha(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_lower_alpha(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_alpha(
            typename T::value_type code_point)
            -> ext::boolean;

    template <ext::string_like T>
    auto is_ascii_alphanumeric(
            typename T::value_type code_point)
            -> ext::boolean;
}

#endif //SBROWSER2_CODE_POINTS_INTERNALS_HPP
