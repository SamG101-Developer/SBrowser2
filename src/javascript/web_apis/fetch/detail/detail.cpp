module;
#include "ext/macros.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>

#include <tl/optional.hpp>
#include <v8-local-handle.h>
#include <v8-object.h>


module apis.fetch.detail;
import apis.fetch.types;

import apis.dom.dom_exception;
import apis.dom.types;

import apis.infra.detail;
import apis.url.types;

import ext.core;


auto fetch::detail::report_timing(fetch_controller_t& controller, v8::Local<v8::Object> global_object) -> void
{
    // Assert that the 'controller' has report timing steps. If this callback exists, then call it with the
    // 'global_object'.
    ext::assert_(!controller.report_timing_steps.empty());
    controller.report_timing_steps(global_object);
}


auto fetch::detail::process_next_manual_redirect(fetch_controller_t& controller) -> void
{
    // Assert that the 'controller' has next manual redirect steps. If this callback exists, then call with no
    // arguments.
    ext::assert_(!controller.next_manual_redirect_steps.empty());
    controller.next_manual_redirect_steps();
}


auto fetch::detail::extract_full_timing_info(fetch_controller_t& controller) -> fetch_timing_info_t*
{
    // Assert that the 'controller' has a full timing info - a struct for saving the timing information. If this struct
    // exists, then return it.
    ext::assert_(controller.full_timing_info != nullptr);
    return controller.full_timing_info.get();
}


auto fetch::detail::abort_fetch_controller(fetch_controller_t& controller, ext::optional<dom::dom_exception&&> error) -> void
{
    // The method of aborting the 'controller' is to set 'controller.state' to ABORTED, and set the serialized error to
    // 'error' or an ABORT_ERR DomException.
    using enum dom::detail::dom_exception_error_t;
    controller.state = fetch_controller_state_t::ABORTED;

    // Prefer the inputted error (if it exists), otherwise create a new DomException, whose type is an ABORT_ERR.
    auto fallback_error = dom::dom_exception{u8"fetch controller has aborted", ABORT_ERR};
    auto abort_error = std::move(error.value_or(fallback_error));

    // Set the serialized 'error' to the 'controller.serialized_error'. If there was a serialization error, then set
    // the 'controller.serialized_error' to the serialization of the 'fallback_error'.
    controller.serialized_abort_reason = ext::js_value_or_fallback(
            html::detail::structured_serialize(std::move(abort_error)),
            html::detail::structured_serialize(std::move(fallback_error)));
}


auto fetch::detail::deserialize_serialized_abort_reason(v8::Local<v8::Object> abort_reason, v8::Local<v8::Context> realm) -> dom::dom_exception
{
    using enum dom::detail::dom_exception_error_t;

    return ext::js_value_or_fallback(
            html::detail::structured_deserialize(abort_reason, realm),
            dom::dom_exception{u8"fetch controller has aborted", ABORT_ERR});
}


auto fetch::detail::terminate_fetch_controller(fetch_controller_t& controller) -> void
{
    // To abort the 'terminated', set its 'state' to TERMINATED.
    controller.state = fetch_controller_state_t::TERMINATED;
}



auto fetch::detail::is_local_scheme(ext::string_view scheme) -> ext::boolean
{
    // Determine if a scheme is a local scheme (match 1 from a fixed set)
    constexpr auto local_schemes = {u"about", u"blob", u"data"};
    return ranges::contains(local_schemes, scheme);
}


auto fetch::detail::is_http_scheme(ext::string_view scheme) -> ext::boolean
{
    // Determine if a scheme is a http scheme (match 1 from a fixed set)
    constexpr auto http_schemes = {u"http", u"https"};
    return ranges::contains(http_schemes, scheme);
}


auto fetch::detail::is_fetch_scheme(ext::string_view scheme) -> ext::boolean
{
    return is_local_scheme(scheme) || is_http_scheme(scheme) || scheme == u"file";
}


auto fetch::detail::is_url_local(url::detail::url_t& url) -> ext::boolean
{return is_local_scheme(url.scheme);}


template <ext::char_like T>
auto fetch::detail::is_http_newline_byte(T character) -> ext::boolean
{return character == 0x0a || character == 0x0d;}


template <ext::char_like T>
auto fetch::detail::is_http_tab_or_space_byte(T character) -> ext::boolean
{return character == 0x09 || character == 0x20;}


template <ext::char_like T>
auto fetch::detail::is_http_whitespace_byte(T character) -> ext::boolean
{return is_http_newline_byte(character) || is_http_tab_or_space_byte(character);}


template <ext::string_like T>
auto fetch::detail::collect_http_quoted_string(T& input, typename T::iterator& position, ext::boolean extract_value_flag) -> T&
{
    // Copy the position as the start position (not a aliased reference) to save the iterator, and create an empty
    // 'value' string which might be returned depending on the 'extract_value_flag' flag. Assert that the current
    // character (at 'position' is not 0x0022)
    auto position_start = position;
    auto value = ext::string{};
    ext::assert_(*position = 0x0022);

    // Advance the position forward 1 prior to looping
    ranges::advance(position, 1);

    while (true)
    {
        value += infra::detail::collect_code_points_not_matching(input, position, 0x0022, 0x005c);
        break_if (position == input.end());

        auto quote_or_backslash = *position;
        ranges::advance(position, 1);

        if (quote_or_backslash == 0x005c)
        {
            value += *position;
            break_if (position == input.end());
            ranges::advance(position, 1);
        }
        else
        {
            ext::assert_(quote_or_backslash == 0x0022);
            break;
        }
    }

    return extract_value_flag
           ? value
           : ext::string{position_start, position};
}


auto fetch::detail::is_cors_safelisted_method(method_t method) -> ext::boolean
{
    using enum method_t;
    auto cors_safelisted_methods = {GET, HEAD, POST};
    return ranges::contains(cors_safelisted_methods, method);
}


auto fetch::detail::is_forbidden_method(method_t method) -> ext::boolean
{
    using enum method_t;
    auto forbidden_methods = {CONNECT, TRACE, TRACK};
    return ranges::contains(forbidden_methods, method);
}


template <fetch::detail::header_value_object_t T, typename U>
auto fetch::detail::get_structured_field_value(
        ext::view_of_t<header_name_t> header_name,
        ext::view_of_t<headers_t> headers) -> U
{
    // Get the raw header value from the 'headers', as a string - this could be a string, string representation of a
    // dictionary, or a string representation of a list; the value is parsed into the correct format (string /
    // dictionary / list), and returned if it is empty.
    auto value = infra::detail::strip_leading_whitespace(get_header_value(header_name));
    return_if(value.empty()) value;

    return value;
}


template <>
auto fetch::detail::get_structured_field_value<fetch::detail::header_value_object_t::DICT>(
        ext::view_of_t <header_name_t> header_name,
        ext::view_of_t <headers_t> headers)
        -> ext::map<header_value_t, header_values_t>
{
    auto dictionary = ext::map<header_value_t, header_values_t>{};
    auto input_string = get_structured_field_value(header_name);
    return_if (input_string.empty()) dictionary;

    return rfc::_8941::parse_dictionary(std::move(input_string)).value_or(std::move(dictionary));
}


template <>
auto fetch::detail::get_structured_field_value<fetch::detail::header_value_object_t::LIST>(
        ext::view_of_t <header_name_t> header_name,
        ext::view_of_t <headers_t> headers)
        -> ext::vector<header_value_t>
{
    auto list = ext::vector<header_values_t>{};
    auto input_string = get_structured_field_value(header_name);
    return_if (input_string.empty()) list;

    return rfc::_8941::parse_list(std::move(input_string)).value_or(std::move(list));
}


template <>
auto fetch::detail::get_structured_field_value<fetch::detail::header_value_object_t::ITEM>(
        ext::view_of_t <header_name_t> header_name,
        ext::view_of_t <headers_t> headers)
        -> header_value_t
{
    auto item = header_value_t{};
    auto input_string = get_structured_field_value(header_name);
    return_if (input_string.empty()) item;

    return rfc::_8941::parse_list(std::move(input_string)).value_or(std::move(item));
}


auto fetch::detail::set_structured_field_value(
        fetch::detail::header_t&& header,
        fetch::detail::headers_t& headers)
        -> void
{
    // Serialize the value of the header (string / dictionary / list, and set a header with the header name and
    // serialized header value, into the 'headers' list
    auto header_name = std::move(header.first);
    auto serialized_value = serialize_structured_fields(std::move(header.second));
    set_header({std::move(header_name), std::move(serialized_value)}, headers);
}


auto fetch::detail::header_list_contains_header(
        ext::view_of_t<header_name_t> header_name,
        ext::view_of_t<headers_t> headers)
        -> ext::boolean
{
    // The 'headers' contain the 'head_name' if any of the pairs in the 'headers' list have the first part of the pair
    // set to a value equal to 'header_name'. The comparison is case-insensitive to convert both to lowercase for the
    // comparisons.
    auto lowercase_header_name = header_name | ranges::views::lowercase | ranges::to_string;
    return ranges::contains(headers | ranges::views::keys, lowercase_header_name, ranges::views::lowercase);
}


auto fetch::detail::get_header_value(
        ext::view_of_t<header_name_t> header_name,
        ext::view_of_t<headers_t> headers)
        -> header_value_t
{
    // Filter all the headers down to headers that have the same name as 'lowercase_header_name', and then transform
    // them to have a COMMA followed by a SPACE. remove teh last occurrence of ", " by matching it to the end character
    // as-well ie ", \0".
    auto lowercase_header_name = header_name | ranges::views::lowercase | ranges::to_string;
    return headers
           | ranges::views::filter(BIND_BACK(ext::pair_key_matches, std::move(lowercase_header_name)))
           | ranges::views::transform([](const header_t& header) {return header.second + char8_t(0x2c) + char8_t(0x20);})
           | ranges::views::remove(ext::string{char16_t(0x002c) + char16_t(0x0020) + '\0'})
           | ranges::to<header_value_t>();
}
