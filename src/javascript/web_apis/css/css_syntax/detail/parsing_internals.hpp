#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX_DETAIL_PARSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX_DETAIL_PARSING_INTERNALS_HPP

#include "ext/expected.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(css/css_syntax)


namespace css::detail
{
    template <typename T>
    auto normalize_into_token_stream(
            T&&)
            -> void;

    auto normalize_into_token_stream(
            ext::vector_view<token_t> input)
            -> ext::vector_view<token_t>;

    auto normalize_into_token_stream(
            ext::string_view input)
            -> ext::vector_view<token_t>;

    /* 5.3.1 */
    template <typename T>
    auto parse(
            T&& input)
            -> parse_result_t;

    /* 5.3.2 */
    template <typename T>
    auto parse_list(
            T&& input)
            -> parse_result_t;

    /* 5.3.3 */
    template <typename T>
    auto parse_style_sheet(
            T&& input,
            ext::string_view location)
            -> parse_result_t;

    /* 5.3.4 */
    template <typename T>
    auto parse_list_of_rules(
            T&& input)
            -> parse_result_t;

    /* 5.3.5 */
    template <typename T>
    auto parse_rule(
            T&& input)
            -> parse_result_t;

    template <typename T>
    auto parse_style_block_contents(
            T&& input)
            -> parse_result_t;

    template <typename T>
    auto parse_list_of_declarations(
            T&& input)
            -> parse_result_t;

    template <typename T>
    auto parse_component_value(
            T&& input)
            -> parse_result_t;

    template <typename T>
    auto parse_comma_separated_list_of_component_value(
            T&& input)
            -> parse_result_t;

    auto consume_list_of_rules(
            ext::string& code_points,
            ext::boolean top_level_flag)
            -> ext::vector<token_t>;

    auto consume_at_rule(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_qualified_rule(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_style_block_contents(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_list_of_declarations(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_declaration(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_component_value(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_simple_block(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto consume_function(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto interpret_urange_syntax(
            ext::string& code_points)
            -> ext::vector<token_t>;

    auto serialize_urange_value(
            ext::number<int> a,
            ext::number<int> b)
            -> ext::string;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX_DETAIL_PARSING_INTERNALS_HPP
