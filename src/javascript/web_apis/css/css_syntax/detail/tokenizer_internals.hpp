#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX_DETAIL_TOKENIZER_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX_DETAIL_TOKENIZER_INTERNALS_HPP


#include "ext/optional.ixx"
#include INCLUDE_INNER_TYPES(css/css_syntax)


namespace css::detail
{
    auto consume_token(
            ext::string code_points)
            -> token_t;

    auto consume_comment(
            ext::string& code_points)
            -> void;

    auto consume_numeric_token(
            ext::string& code_points)
            -> token_t;

    auto consume_ident_like_token(
            ext::string& code_points)
            -> token_t;

    auto consume_string_token(
            ext::string& code_points)
            -> token_t;

    auto consume_url_token(
            ext::string& code_points)
            -> token_t;

    auto consume_escaped_code_point(
            ext::string& code_points)
            -> token_t;

    auto consume_ident_sequence(
            ext::string& code_points)
            -> token_t;

    auto consume_number(
            ext::string& code_points)
            -> token_t;

    auto consume_remnants_of_bad_url(
            ext::string& code_points)
            -> token_t;

    auto check_if_2_code_points_are_valid_escape(
            char code_point_1,
            char code_point_2)
            -> ext::boolean;

    auto check_if_3_code_points_are_valid_escape(
            char code_point_1,
            char code_point_2,
            char code_point_3)
            -> ext::boolean;

    auto check_if_3_code_points_would_start_number(
            char code_point_1,
            char code_point_2,
            char code_point_3)
            -> ext::boolean;

    auto convert_string_to_number(
            ext::string_view string)
            -> ext::number<int>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX_DETAIL_TOKENIZER_INTERNALS_HPP
