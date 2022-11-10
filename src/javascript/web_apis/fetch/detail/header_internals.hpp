#pragma once
#ifndef SBROWSER2_HEADER_INTERNALS_HPP
#define SBROWSER2_HEADER_INTERNALS_HPP


#include <tuple>
#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(fetch)

namespace fetch::detail // TODO : const ...& vs ..._view
{
    DEFINE_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPES(header_value_object_t, header_value_variable, void*);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::DICT, ext::map<header_value_t COMMA header_values_t>);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::LIST, ext::vector<header_value_t>);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::ITEM, header_value_t);

    template <header_value_object_t T>
    auto get_structured_field_value(
            const header_name_t& header_name,
            const headers_t& headers)
            -> header_value_variable_t<T>;

    template <>
    auto get_structured_field_value<header_value_object_t::DICT>(
            const header_name_t& header_name,
            const headers_t& headers)
            -> ext::map<header_value_t, header_values_t>;

    template <>
    auto get_structured_field_value<header_value_object_t::LIST>(
            const header_name_t& header_name,
            const headers_t& headers)
            -> ext::vector<header_value_t>;

    template <>
    auto get_structured_field_value<header_value_object_t::ITEM>(
            const header_name_t& header_name,
            const headers_t& headers)
            -> header_value_t;

    auto set_structured_field_value(
            const header_t& header,
            const headers_t& headers)
            -> void;

    auto header_list_contains_header(
            const headers_t& headers,
            const header_name_t& header_name)
            -> ext::boolean;

    auto get_header_value(
            const header_name_t& header_name,
            const headers_t& headers)
            -> header_value_t;

    auto get_decode_split_value(
            const header_name_t& header_name,
            const headers_t& headers)
            -> header_names_t;

    auto append_header(
            const header_t& header,
            headers_t& headers)
            -> void;

    auto delete_header(
            const header_name_t& header_name,
            headers_t& headers)
            -> void;

    auto set_header(
            const header_t& header,
            headers_t& headers)
            -> void;

    auto combine_header(
            const header_t& header,
            const headers_t& headers)
            -> void;

    auto convert_header_names_to_sorted_lowercase_set(
            const header_names_t& header_names)
            -> header_names_t;

    auto sort_and_combine(
            const headers_t& headers)
            -> headers_t;

    auto is_cors_safelisted_request_header(
            const header_t& header)
            -> ext::boolean;

    auto is_cors_unsafe_request_header_byte(
            char byte)
            -> ext::boolean;

    auto cors_unsafe_request_header_names(
            const headers_t& headers)
            -> ext::vector<ext::string>;

    auto is_cors_non_wildcard_request_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto is_privileged_no_cors_request_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto is_cors_safelisted_response_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto is_no_cors_safelisted_request_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto is_no_cors_safelisted_request_header(
            const header_t& header)
            -> ext::boolean;

    auto is_forbidden_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto is_forbidden_response_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto is_request_body_header_name(
            const header_name_t& header_name)
            -> ext::boolean;

    auto extract_header_values(
            const header_t& header)
            -> header_values_t;

    auto extract_header_list_values(
            const header_name_t& header_name,
            const header_t& header)
            -> header_values_t;

    auto is_simple_range_header_value(
            header_value_t header_value)
            -> ext::boolean;
}


#endif //SBROWSER2_HEADER_INTERNALS_HPP
