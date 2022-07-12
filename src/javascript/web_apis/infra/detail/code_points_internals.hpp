#ifndef SBROWSER2_CODE_POINTS_INTERNALS_HPP
#define SBROWSER2_CODE_POINTS_INTERNALS_HPP

#include "ext/boolean.hpp"

namespace infra::detail::code_points_internals
{
    namespace literals
    {
        auto LF = char(0x000a);
        auto CR = char(0x000d);
        auto SPACE = char(0x0020);
    }

    auto is_surrogate(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_scalar(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_non_character(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_code_point(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_tab_or_newline(
            char32_t code_point)
            -> ext::boolean;

    auto is_ascii_newline(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_whitespace(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_c0_control(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_c0_control_or_space(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_control(
            char32_t code_point)
            -> ext::boolean;

    auto is_ascii_digit(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_upper_hex_digit(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_lower_hex_digit(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_hex_digit(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_upper_alpha(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_lower_alpha(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_alpha(
            char32_t code_point)
            -> ext::boolean;
    
    auto is_ascii_alphanumeric(
            char32_t code_point)
            -> ext::boolean;
}

#endif //SBROWSER2_CODE_POINTS_INTERNALS_HPP
