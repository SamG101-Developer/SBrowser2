module;
#include "ext/macros.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/drop_last.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/transform.hpp>

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
    auto lowercase_header_name = header_name | ranges::views::lowercase | ranges::to_any_string;
    return ranges::contains(headers | ranges::views::keys, lowercase_header_name, ranges::views::lowercase);
}


auto fetch::detail::get_header_value(
        ext::view_of_t<header_name_t> header_name,
        ext::view_of_t<headers_t> headers)
        -> header_value_t
{
    // Filter all the headers down to headers that have the same name as 'lowercase_header_name', and then transform
    // them to have a COMMA followed by a SPACE. Remove the last occurrence of ", " by dropping the last 2 characters of
    // the range.
    auto lowercase_header_name = header_name | ranges::views::lowercase | ranges::to_any_string;
    return headers
           | ranges::views::filter(ext::bind_back(ext::pair_key_matches, std::move(lowercase_header_name)))
           | ranges::views::transform([](auto&& header) {return header.second + header_value_t::value_type(0x2c) + header_value_t::value_type(0x20);})
           | ranges::views::drop_last(2)
           | ranges::to<header_value_t>();
}


fetch::detail::get_decode_split_name(
        ext::view_of_t<header_name_t> header_name,
        ext::view_of_t<headers_t> headers)
        -> header_names
{
    // Get the header value for the 'header_name' in 'headers', and return an empty list if there are no values
    // associated with the 'header_name' because the 'header_name' key doesn;t contain any values.
    auto input = get_header_value(header_name, headers);
    return input.empty() ? {} : get_decode_split_value(std::move(input));
}


auto fetch::detail::get_decode_split_value(
        ext::view_of_t<header_name_t> header_value,
        ext::view_of_t<headers_t> headers)
        -> header_names_t
{
    auto input = infra::detail::isomorphic_encode(value);

    // Set the 'position' to point at the start of the string, and initialize the current 'value, and the final 'values'
    // list that will be returned.
    auto position = input.begin();
    auto values = header_names_t{};
    auto temporary_value = ext::string{};

    // Loop until the 'position' pointer points to the end of the header value string ('input').
    while (position != input.end())
    {
        // Append the collection of code points up until a SPEECH_MARK or COMMA from the 'input', starting at the
        // pointer 'position'; these code points are automatically removed from the 'input' string.
        temporary_value += infra::detail::collect_code_points_not_matching(input, position, 0x0022, 0x002c);

        // Re-check the character at the end position, after collecting the above code points from 'input' -- otherwise
        // could be dereferencing a nullptr iterator.
        if (position != input.end())
        {
            // If the current 'position' pointer is pointing to a SPEECH_MARK, then collect the html-quoted string from
            // the 'input' (starting from 'position'), and remove it from the 'input'. append this extracted string to
            // the 'value', and continue if the 'input's end pointer hasn't been reached yet.
            if (*position == header_value_t::value_type(0x0022))
            {
                temporary_value += collect_http_quoted_string(input, position);
                continue_if(position != input.end());
            }

            // Otherwise, the current character must be a comma, so assert this, and then increment the 'position'
            // iterator to inspect the next character (or to reach the end of the string).
            else
            {
                ext::assert_(*position == char(0x002c));
                ranges::advance(position, 1);
            }
        }

        // Append the new value with spaces and tabs removed from the back and front of the string, and then reset the
        // value string for the next iteration pass.
        values.emplace_back(temporary_value | ranges::actions::remove_if(is_http_tab_or_space));
        temporary_value = {};
    }

    // Return the list of header values that have been decoded and split into a list.
    return values;
}



auto fetch::detail::append_header(fetch::detail::header_t&& header, fetch::detail::headers_t& headers) -> void
{
    // If the 'header' already exists in the 'headers', then convert 'header.name' to the matching case of the existing
    // entry of that name.
    if (header_list_contains_header(header.first, headers))
    {
        decltype(auto) existing_header = *ranges::first_where(headers, ext::bind_back(ext::cmp::eq, header.first | ranges::views::lowercase, ranges::views::lowercase)));
        header.first = existing_header.first
    }

    // Emplace the 'header' into the 'headers'.
    headers.emplace_back(std::move(header));
}


auto fetch::detail::delete_header(ext::view_of_t<header_name_t> header_name, fetch::detail::headers_t& headers) -> void
{
    // Remove the individual headers from the 'headers' list whose key value matches 'header_name' (can be more
    // than one header with a matching name to 'header_name'.
    headers |= ranges::actions::remove_if(headers, ext::bind_back(ext::cmp::eq, header.first | ranges::views::lowercase, ranges::views::lowercase));
}


auto fetch::detail::set_header(fetch::detail::header_t&& header, fetch::detail::headers_t& headers) -> void
{
    // If any of the headers have their name matching the new 'header' name, then perform specific replacement steps --
    // set the value of the 'existing_header' to 'header.second', so that this header maintains its position in the
    // 'headers'. Remove other occurences of headers in the 'headers' list whose key matches 'header.first'.
    if (header_list_contains_header(header.first, headers))
    {
        decltype(auto) existing_header = *ranges::first_where(headers, ext::bind_back(ext::cmp::eq, header.first | ranges::views::lowercase, ranges::views::lowercase)));
        existing_header.second = std::move(header.second);
        headers
                |= ranges::actions::drop_if_n(ext::bind_back(ext::cmp::eq, header.first | ranges::views::lowercase, ranges::views::lowercase), 1)
                |  ranges::actions::remove_if(ext::bind_back(ext::cmp::eq, header.first | ranges::views::lowercase, ranges::views::lowercase));
    }

    // Otherwise just append the header to the list
    else
        append_header(std::move(header), headers);
}
