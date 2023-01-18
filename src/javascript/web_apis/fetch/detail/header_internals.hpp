#pragma once
#ifndef SBROWSER2_HEADER_INTERNALS_HPP
#define SBROWSER2_HEADER_INTERNALS_HPP


#include "ext/expected.ixx"
#include "ext/span.hpp"

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(fetch)


// TODO : const ...& vs ..._view
// TODO : parameter order (name, list) or (list, name) etc
namespace fetch::detail
{


    DEFINE_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPES(header_value_object_t, header_value_variable, void*);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::DICT, ext::map<header_value_t COMMA header_values_t>);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::LIST, ext::vector<header_value_t>);
    ADD_TEMPLATE_FUNCTION_SPECIALIZATION_RETURN_TYPE(header_value_variable, header_value_object_t::ITEM, header_value_t);









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


}


#endif //SBROWSER2_HEADER_INTERNALS_HPP
