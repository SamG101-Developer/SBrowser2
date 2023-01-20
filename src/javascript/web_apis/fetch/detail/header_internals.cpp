#include "header_internals.hpp"






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

#include <range/v3/view/iota.hpp>

#include <range/v3/view/reverse.hpp>
#include <range/v3/view/transform.hpp>



















auto fetch::detail::combine_header(fetch::detail::header_t&& header, const fetch::detail::headers_t& headers) -> void
{
    auto lowercase_header = std::make_pair(header.first | ranges::views::lowercase | ranges::to<ext::string>, header.second);

    // if any of the headers have their name matching the new 'header' name, then perform specific combinations steps;
    // otherwise, just append the new header
    if (ranges::contains(headers | ranges::views::keys, lowercase_header.first))
    {
        // create a method that will be used multiple times; it checks all the headers, and identifies headers that
        // have a matching header name
        auto header_matches = [lowercase_header](const header_t& existing_header) {return existing_header.first == lowercase_header.first;};

        // append to the value of the first occurrence of the lowercase header name with a COMMA and then a SPACE,
        // followed by the new header value
        (*ranges::first_where(headers, header_matches)).second += char(0x2c) + char(0x20) + lowercase_header.second;
        return;
    }

    // otherwise, the 'header' doesn't exist, so append it to the end of the 'headers'
    append_header(lowercase_header, headers);
}


auto fetch::detail::convert_header_names_to_sorted_lowercase_set(ext::span_of_t<header_names_t> header_names) -> header_names_t
{
    // transform the 'header_names' to lowercase strings, using the infra 'byte_less_than' functor as the sorting
    // method; object is still a range
    auto sorted_lowercase_header_names = ranges::sort(
            header_names | ranges::views::transform([](const header_name_t& header_name) {header_name | ranges::views::lowercase | ranges::to<ext::string>;}),
            infra::detail::is_code_unit_less_than);

    // return the range converted to list of strings (header names)
    return sorted_lowercase_header_names | ranges::to<ext::vector<ext::string>>;
}


auto fetch::detail::sort_and_combine(const fetch::detail::headers_t& headers) -> headers_t
{
    headers_t formatted_headers;
    auto sorted_lowercase_header_names = convert_header_names_to_sorted_lowercase_set(headers | ranges::views::keys | ranges::to<ext::vector<ext::string>>);
    for (ext::string_view header_name: sorted_lowercase_header_names)
    {
        auto header_value = get_header_value(header_name, headers);
        assert(!header_value.empty());
        append_header({header_name, header_value}, formatted_headers);
    }

    return formatted_headers;
}


auto fetch::detail::is_cors_safelisted_request_header(fetch::detail::header_t&& header) -> ext::boolean
{
    return_if (header.second.size() > 123) false;
    auto lowercase_header_name = header.first | ranges::views::lowercase | ranges::to<ext::string>;

    string_switch(lowercase_header_name)
    {
        string_case(u"accept"):
            return_if (ranges::any_of(header.second, is_cors_unsafe_request_header_byte)) false;

        string_case(u"accept-language"):
        string_case(u"content-language"):
            auto stripped_header_value = header.second
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ranges::views::closed_iota(0x30, 0x39)))
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ranges::views::closed_iota(0x41, 0x5a)))
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ranges::views::closed_iota(0x61, 0x7a)))
                    | ranges::views::remove_if(ext::bind_front(ranges::contains, ext::initializer_list<char8_t>{0x20, 0x2a, 0x2c, 0x2d, 0x2e, 0x3b, 0x3d}));

            return_if (!stripped_header_value.empty()) false;

        string_case(u"content-type"):
        {
            return_if (ranges::any_of(header.second, is_cors_unsafe_request_header_byte)) false;
            auto mime_type = mime_sniffing::mime_type_internals::parse(header.second);
            return_if(mime_type.empty()) false;
            return_if(!ranges::contains(ext::initializer_list<ext::string>{u"application/x-www-form-urlencoded", u"multipart/form-data", u"text/plain"}, mime_type.essence)) false;
        }

        string_case(u"range");
            return_if (!is_simple_range_header_value(header.second));

        string_default:
            return false;
    }

    return true;
}


template <ext::string_like T>
auto fetch::detail::normalize(T& potential_value) -> T&
{
    return infra::detail::strip_leading_and_trailing_ascii_whitespace(potential_value);
}
