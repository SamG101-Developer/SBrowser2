#pragma once
#ifndef SBROWSER2_HEADER_INTERNALS_HPP
#define SBROWSER2_HEADER_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/expected.hpp"
#include "ext/span.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(fetch)


// TODO : const ...& vs ..._view
// TODO : parameter order (name, list) or (list, name) etc
namespace fetch::detail
{
    auto is_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto is_header_value(
            ext::view_of_t<header_value_t> header_value)
            -> ext::boolean;

    DEFINE_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPES(header_value_object_t, header_value_variable, void*);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::DICT, ext::map<header_value_t COMMA header_values_t>);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::LIST, ext::vector<header_value_t>);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::ITEM, header_value_t);

    template <header_value_object_t T>
    auto get_structured_field_value(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> header_value_variable_t<T>;

    template <>
    auto get_structured_field_value<header_value_object_t::DICT>(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> ext::map<header_value_t, header_values_t>;

    template <>
    auto get_structured_field_value<header_value_object_t::LIST>(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> ext::vector<header_value_t>;

    template <>
    auto get_structured_field_value<header_value_object_t::ITEM>(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> header_value_t;

    auto set_structured_field_value(
            header_t&& header,
            headers_t& headers)
            -> void;

    auto header_list_contains_header(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> ext::boolean;

    auto get_header_value(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> header_value_t;

    auto get_decode_split_value(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> header_names_t;

    auto append_header(
            header_t&& header,
            headers_t& headers)
            -> void;

    auto delete_header(
            ext::view_of_t<header_name_t> header_name,
            headers_t& headers)
            -> void;

    auto set_header(
            header_t&& header,
            headers_t& headers)
            -> void;

    auto combine_header(
            header_t&& header,
            const headers_t& headers)
            -> void;

    auto convert_header_names_to_sorted_lowercase_set(
            ext::span_of_t<header_names_t> header_names)
            -> header_names_t;

    auto sort_and_combine(
            const headers_t& headers)
            -> headers_t;

    auto is_cors_safelisted_request_header(
            header_t&& header)
            -> ext::boolean;

    template <ext::char_like T>
    auto is_cors_unsafe_request_header_byte(
            T byte)
            -> ext::boolean;

    auto cors_unsafe_request_header_names(
            ext::span_of_t<headers_t> headers)
            -> ext::vector<ext::string>;

    auto is_cors_non_wildcard_request_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto is_privileged_no_cors_request_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto is_cors_safelisted_response_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto is_no_cors_safelisted_request_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto is_no_cors_safelisted_request_header(
            header_t&& header)
            -> ext::boolean;

    auto is_forbidden_request_header(
            header_t&& header)
            -> ext::boolean;

    auto is_forbidden_response_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto is_request_body_header_name(
            ext::view_of_t<header_name_t> header_name)
            -> ext::boolean;

    auto extract_header_values(
            ext::view_of_t<header_name_t> header)
            -> ext::expected<header_values_t>;

    auto extract_header_list_values(
            ext::view_of_t<header_name_t> header_name,
            ext::span_of_t<headers_t> headers)
            -> ext::expected<header_values_t>;

    auto is_simple_range_header_value(
            ext::view_of_t<header_value_t> header_value)
            -> ext::boolean;

    template <ext::string_like T>
    auto normalize(
            T& potential_value)
            -> T&;
}


#endif //SBROWSER2_HEADER_INTERNALS_HPP
