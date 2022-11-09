#ifndef SBROWSER2_CODE_POINTS_INTERNALS_HPP
#define SBROWSER2_CODE_POINTS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"

#define DIGITS '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'

namespace infra::detail
{
    enum literals : char
    {
        LF = char(0x000a),
        CR = char(0x000d),
        SPACE = char(0x0020)
    };

    auto is_surrogate(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_scalar(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_non_character(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_code_point(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_tab_or_newline(
            ext::string::value_type code_point)
            -> ext::boolean;

    auto is_ascii_newline(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_whitespace(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_c0_control(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_c0_control_or_space(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_control(
            ext::string::value_type code_point)
            -> ext::boolean;

    auto is_ascii_digit(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_upper_hex_digit(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_lower_hex_digit(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_hex_digit(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_upper_alpha(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_lower_alpha(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_alpha(
            ext::string::value_type code_point)
            -> ext::boolean;
    
    auto is_ascii_alphanumeric(
            ext::string::value_type code_point)
            -> ext::boolean;
}

#endif //SBROWSER2_CODE_POINTS_INTERNALS_HPP
