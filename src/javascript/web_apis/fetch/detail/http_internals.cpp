#include "http_internals.hpp"

#include "infra/detail/infra_strings_internals.hpp"
#include "range/v3/iterator/operations.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/contains.hpp>


auto fetch::detail::is_local_scheme(ext::string_view scheme) -> ext::boolean
{
    auto local_schemes = {u"about", u"blob", u"data"};
    return ranges::contains(local_schemes, scheme);
}


auto fetch::detail::is_http_scheme(ext::string_view scheme) -> ext::boolean
{
    auto http_schemes = {u"http", u"https"};
    return ranges::contains(http_schemes, scheme);
}


auto fetch::detail::is_fetch_scheme(ext::string_view scheme) -> ext::boolean
{
    return is_local_scheme(scheme) || is_http_scheme(scheme) || scheme == u"file";
}


auto fetch::detail::is_url_local(url::detail::url_t& url) -> ext::boolean
{
    // a url is local if its scheme is a local scheme; these schemes are the "about", "blob" and "data" schemes
    return is_local_scheme(url.scheme);
}


auto fetch::detail::is_http_newline_byte(char8_t character) -> ext::boolean
{
    return character == 0x0a || character == 0x0d;
}


auto fetch::detail::is_http_tab_or_space_byte(char8_t character) -> ext::boolean
{
    return character == 0x09 || character == 0x20;
}


auto fetch::detail::is_http_whitespace_byte(char8_t character) -> ext::boolean
{
    return is_http_newline_byte(character) || is_http_tab_or_space_byte(character);
}


auto fetch::detail::collect_http_quoted_string(
        ext::string& input,
        ext::string::iterator& position,
        ext::boolean extract_value_flag)
        -> ext::string
{
    auto position_start = position;
    auto value = ext::string{};
    assert(*position = char16_t(0x0022));

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
            assert(quote_or_backslash == 0x0022);
            break;
        }
    }

    return extract_value_flag
            ? value
            : ext::string{position_start, position};
}
