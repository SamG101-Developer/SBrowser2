#include "header_internals.hpp"

#include "ext/functional.hpp"
#include "ext/pair.hpp"
#include "ext/ranges.hpp"

#include "infra/detail/infra_strings_internals.hpp"
#include "fetch/detail/http_internals.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/transform.hpp>


auto fetch::detail::header_internals::get_structured_field_value(
        header_value_object_t type,
        header_name_t header_name,
        const headers_t& headers)
        -> header_value_t
{
    // get the raw header value from the 'headers', as a string - this could be a string, string representation of a
    // dictionary, or a string representation of a list; the value is parsed into the correct format (string /
    // dictionary / list), and returned if it is empty
    auto value = get_header_value(header_name, headers);
    return_if(value.empty()) value;

    // parse the value into the correct type and return it (variant return type of string, dictionary or list). parsing
    // similar to loading a json.loads
    auto parsed_value = parse_structured_value(value, type);
    return parsed_value;
}


auto fetch::detail::header_internals::set_structured_field_value(
        const header_t& header,
        const headers_t& headers)
        -> void
{
    // serialize the value of the header (string / dictionary / list, and set a header with the header name and
    // serialized header value, into the 'headers' list
    const auto& header_name = header.first;
    auto serialized_value = serialize_structured_fields(header.second);
    set_header({header_name, serialized_value}, headers);
}


auto fetch::detail::header_internals::header_list_contains_header(
        const headers_t& headers,
        header_name_t header_name)
        -> ext::boolean
{
    // 'headers' contains the 'head_name' if any of the pairs in the 'headers' list have the first part of the pair set
    // to a value equal to 'header_name'
    return ranges::contains(headers | ranges::views::keys, header_name);
}


auto fetch::detail::header_internals::get_header_value(
        const header_name_t header_name,
        const headers_t& headers)
        -> header_value_t
{
    // convert the 'header_name' to lowercase for comparisons (the headers stored in the list are all in lowercase
    // already; this conversion is done in the 'set_header(...)' method for uniformity between all header names inserted
    // into the 'headers'
    auto lowercase_header_name = header_name | ranges::views::lowercase() | ranges::to<ext::string>();

    // filter all the headers down to headers that have the same name as 'lowercase_header_name', and then transform
    // them to have a COMMA followed by a SPACE. remove teh last occurrence of ", " by matching it to the end character
    // as-well ie ", \0"
    auto matching_headers_values = headers
            | ranges::views::filter([lowercase_header_name](const header_t& header) {return header.first == lowercase_header_name;})
            | ranges::views::transform([](const header_t& header) {return header.second + char(0x2c) + char(0x20);})
            | ranges::views::remove(ext::string{} + char(0x2c) + char(0x20) + '\0');

    // join the header values into one string and return it - this will make the header values look like
    // "val1, val2, val3"
    auto joined_matching_headers_values = matching_headers_values | ranges::to<ext::string>;
    return joined_matching_headers_values;
}


auto fetch::detail::header_internals::get_decode_split_value(
        const header_name_t header_name,
        const headers_t& headers)
        -> header_names_t
{
    // get the header value for the 'header_name' in 'headers', and return an empty list if there are no values
    // associated with the 'header_name'
    ext::string input = get_header_value(header_name, headers);
    return_if(input.empty()) {};

    // set the 'position' to point at the start of the string, and initialize the current 'value, and the final 'values'
    // list that will be returned
    auto position = input.begin();
    header_names_t values;
    ext::string value;

    // loop until the 'position' pointer points to the end of the header value string ('input')
    while (position != input.end())
    {
        // append the collection of code points up until a SPEECH_MARK or COMMA from the 'input', starting at the
        // pointer 'position'; these code points are automatically removed from the 'input' string
        value += infra::detail::infra_string_internals::collect_code_points_not_matching(input, position, char(0x0022), char(0x002c));
        if (position != input.end())
        {
            // if the current 'position' pointer is pointing to a SPEECH_MARK, then collect the html-quoted string from
            // the 'input' (starting from 'position'), and remove it from the 'input'. append this extracted string to
            // the 'value', and continue if the 'input's end pointer hasn't been reached yet
            if (*position == char(0x022))
            {
                value += http_internals::collect_http_quoted_string(input, position);
                continue_if(position != input.end());
            }

            // otherwise, the current character must be a comma, so assert this, and then increment the 'position'
            // iterator to inspect the next character (or to reach the end of the string)
            else
            {
                assert(*position == char(0x002c));
                ++position;
            }
        }

        // append the new value with spaces and tabs removed from the back and front of the string, and then reset the
        // value string for the next iteration pass
        values.push_back(infra::detail::infra_string_internals::strip_leading_and_trailing_ascii_whitespace(value));
        value = "";
    }

    // return the list of header values that have been decoded and split into a list
    return values;
}


auto fetch::detail::header_internals::append_header(
        const header_t& header,
        const headers_t& headers)
        -> void
{
    // append the 'header' to the end of the 'headers' list
    headers.push_back(&header);
}


auto fetch::detail::header_internals::delete_header(
        const header_name_t header_name,
        headers_t& headers)
        -> void
{
    // convert the 'header_name' to lowercase for comparisons (the headers stored in the list are all in lowercase
    // already; this conversion is done in the 'set_header(...)' method for uniformity between all header names inserted
    // into the 'headers'
    auto lowercase_header_name = header_name | ranges::views::lowercase() | ranges::to<ext::string>;

    // remove the individual headers from the 'headers' list whose key value matches 'header_name' (can be more
    // than one header ith a matching name to 'header_name'
    headers
            |= ranges::actions::remove_if([lowercase_header_name](const header_t& header) {return header.first == lowercase_header_name;});
}


auto fetch::detail::header_internals::set_header(
        const header_t& header,
        const headers_t& headers)
        -> void
{
    auto lowercase_header = std::make_pair(header.first | ranges::views::lowercase() | ranges::to<ext::string>, header.second);

    // if any of the headers have their name matching the new 'header' name, then perform specific replacement steps;
    // otherwise, just append the new header
    if (ranges::contains(headers | ranges::views::keys, lowercase_header.first))
    {
        // create a method that will be used multiple times; it checks all the headers, and identifies headers that
        // have a matching header name
        auto header_matches = [lowercase_header](const header_t& existing_header) {return existing_header.first == lowercase_header.first;};

        // set the value of the first occurrence of the lowercase header name to the new value (maintains the index),
        // and remove all other occurrences of headers with the same name
        ranges::first_where(headers, header_matches).second = lowercase_header.second;
        ranges::remove_if(ranges::find_if(headers, header_matches) + 1, headers.end(), header_matches);
        return;
    }

    // otherwise, the 'header' doesn't exist, so append it to the end of the 'headers'
    append_header(lowercase_header, headers);
}


auto fetch::detail::header_internals::combine_header(
        const header_t& header,
        const headers_t& headers)
        -> void
{
    auto lowercase_header = std::make_pair(header.first | ranges::views::lowercase() | ranges::to<ext::string>, header.second);

    // if any of the headers have their name matching the new 'header' name, then perform specific combinations steps;
    // otherwise, just append the new header
    if (ranges::contains(headers | ranges::views::keys, lowercase_header.first))
    {
        // create a method that will be used multiple times; it checks all the headers, and identifies headers that
        // have a matching header name
        auto header_matches = [lowercase_header](const header_t& existing_header) {return existing_header.first == lowercase_header.first;};

        // append to the value of the first occurrence of the lowercase header name with a COMMA and then a SPACE,
        // followed by the new header value
        ranges::first_where(headers, header_matches).second += char(0x2c) + char(0x20) + lowercase_header.second;
        return;
    }

    // otherwise, the 'header' doesn't exist, so append it to the end of the 'headers'
    append_header(lowercase_header, headers);
}


auto fetch::detail::header_internals::convert_header_names_to_sorted_lowercase_set(
        const header_names_t& header_names)
        -> header_names_t
{
    // transform the 'header_names' to lowercase strings, using the infra 'byte_less_than' functor as the sorting
    // method; object is still a range
    auto sorted_lowercase_header_names = ranges::sort(
            header_names | ranges::views::transform([](const header_name_t header_name) {header_name | ranges::views::lowercase() | ranges::to<ext::string>;}),
            infra::detail::infra_string_internals::byte_less_than);

    // return the range converted to list of strings (header names)
    return sorted_lowercase_header_names | ranges::to<ext::string_vector>;
}


auto fetch::detail::header_internals::sort_and_combine(
        const headers_t& headers)
        -> headers_t
{
    headers_t formatted_headers;
    auto sorted_lowercase_header_names = convert_header_names_to_sorted_lowercase_set(headers | ranges::views::keys | ranges::to<ext::string_vector>);
    for (ext::string_view header_name: sorted_lowercase_header_names)
    {
        auto header_value = get_header_value(header_name, headers);
        assert(!header_value.empty());
        append_header({header_name, header_value}, formatted_headers);
    }

    return formatted_headers;
}


auto fetch::detail::header_internals::is_cors_safelisted_request_header(
        const header_t& header)
        -> ext::boolean
{
    return_if (header.second.size() > 123) false;
    auto lowercase_header_name = header.first | ranges::views::lowercase() | ranges::to<ext::string>;

    string_switch(lowercase_header_name.c_str())
    {
        string_case("accept"):
            return_if (ranges::any_of(header.second, is_cors_unsafe_request_header_byte)) false;

        string_case("accept-language"):
        string_case("content-language"):
            auto stripped_header_value = header.second
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ranges::views::closed_iota(0x30, 0x39)))
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ranges::views::closed_iota(0x41, 0x5a)))
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ranges::views::closed_iota(0x61, 0x7a)))
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, std::initializer_list<char>{0x20, 0x2a, 0x2c, 0x2d, 0x2e, 0x3b, 0x3d}));

            return_if (!stripped_header_value.empty()) false;

        string_case("content-type"):
        {
            return_if (ranges::any_of(header.second, is_cors_unsafe_request_header_byte)) false;
            auto mime_type = mime_sniffing::mime_type_internals::parse(header.second);
            return_if(mime_type.empty()) false;
            return_if(!ranges::contains(std::initializer_list<ext::string>{"application/x-www-form-urlencoded", "multipart/form-data", "text/plain"}, mime_type.essence)) false;
        }

        string_case("range");
            return_if (!is_simple_range_header_value(header.second));

        string_default:
            return false;
    }

    return true;
}
