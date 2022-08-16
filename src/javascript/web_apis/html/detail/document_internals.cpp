#include "document_internals.hpp"

#include "ext/boolean.hpp"
#include "ext/ranges.hpp"
#include "javascript/environment/reflection.hpp"

#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/document.hpp"

#include "html/elements/html_base_element.hpp"
#include "html/detail/context_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"

#include "infra/detail/code_points_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"

#include "permissions_policy/detail/algorithm_internals.hpp"

#include <magic_enum.hpp>


auto html::detail::is_cookie_averse_document(
        const dom::nodes::document* document)
        -> ext::boolean
{
    // a Document is a cookie averse document if it doesn't have a browsing context, and the scheme of the URL is not
    // HTTPS - this is because cookies need to be transported securely (HTTPS ensures this), and a browsing context
    // ensures that cookies are only shred to the correct Documents
    return !document->m_browsing_context || document->url()->scheme() != "https";
}


auto html::detail::fallback_base_url(
        const dom::nodes::document* document)
        -> ext::string
{
    // TODO : iFrame stuff
    return document->url() == "about:blank" && document->m_browsing_context->creator_base_url
            ? document->m_browsing_context->creator_base_url
            : document->url();
}


auto html::detail::document_base_url(
        const dom::nodes::document* document)
        -> ext::string
{
    auto html_base_element_descendants = dom::detail::descendants(document)
            | ranges::views::cast_all_to<elements::html_base_element*>()
            | ranges::views::filter([](elements::html_base_element* element) {JS_REALM_GET_RELEVANT(element) return reflect_has_attribute_value(element, "href", element_relevant);});

    return html_base_element_descendants.empty()
            ? fallback_base_url(document)
            : html_base_element_descendants.front()->m_frozen_base_url;
}


auto html::detail::shared_declarative_refresh_steps(
        const dom::nodes::document* document,
        ext::string&& input,
        elements::html_meta_element* meta) -> void
{
    return_if (document->m_will_declaratively_refresh);

    // set the 'position' to point to the start of the 'input' string. collect all the whitespace character from the
    // beginning of the 'input' (strip leading spaces)
    auto position = input.begin();
    infra::detail::infra_string_internals::collect_ascii_whitespace(input, position);

    // get the time as a string, by collecting digits from the 'input' string. if there is no 'time_string' (incorrect
    // serialization format), or the next character in the string after the digits is not a '.', then return early.
    // parse the 'time_string' into an integer 'time'
    ext::string time_string = infra::detail::infra_string_internals::collect_code_points_matching(input, position, DIGITS);
    return_if(time_string.empty() && *position != '.');
    ext::number<int> time = std::stoi(time_string);

    // collect all the digits and decimal points after the 'time_string' that was found in the 'input' string. drop all
    // these characters - they are not needed for anything, but there is no issue including them (allows floats /
    // doubles to be directly parsed in without needing an integer cast - this method does that automatically)
    infra::detail::infra_string_internals::collect_code_points_matching(input, position, DIGITS, char(0x002e));
    auto url_record = *document->url(); // Deliberate copy

    // if the current position isn't at the end of the string (ie the 'input' doesn't only contain a 'time_string' and
    // extra numbers), then return if the next character is not a COMMA / SEMICOLON / SPACE, otherwise skip any spaces
    // and verify that there is a COMMA / SEMICOLON
    if (position != input.end())
    {
        auto return_characters = {char(0x003b), char(0x002c)};

        infra::detail::infra_string_internals::collect_ascii_whitespace(input, position);
        return_if(!ranges::contains(return_characters, *position));
        ranges::advance(position, 1);
        infra::detail::infra_string_internals::collect_ascii_whitespace(input, position);
    }

    do
    {
        // the 'url_string' is the substring of the 'input', starting from teh current 'position', and to the end of the
        // 'input' - this string will be modified via substringing (replacing leading / trailing characters etc)
        auto url_string = ranges::subrange(position, input.end()) | ranges::to<ext::string>();

        // the 'skip_quotes' lambda gets the quote character if it exists: either APOSTROPHE / SPEECH_MARK. this
        // character is advanced over, and the 'url_string' is substringed from this 'quote' character to the next
        // 'quote' character (extracts url from quotes). if a second 'quote' character isn't found, then the substring
        // ends at the end of the 'input'
        auto skip_quotes = [document, &url_string, &position]()
        {
            auto quote = *position == 0x0027 || *position == 0x0022 ? *position : '\0';
            if (quote) ranges::advance(position, 1);
            url_string = ranges::subrange(position, url_string.end()) | ranges::to<ext::string>();
            if (quote && ranges::contains(url_string, quote))
                url_string = ranges::subrange(url_string.begin(), ranges::find(url_string.begin() + 1, url_string.end(), quote));

            // parse the url
            return detail::miscellaneous_internals::parse_url(url_string, document);
        };

        // url will either be:
        //  - URL="https://www.example.com"
        //  - "https://www.example.com"
        // if the above format isn't met, then the 'url_record' is left as a null URL, and the block of code is broken
        // from early


        // if the current character at 'position' is a 'u' or 'U', then advance over it, and move onto analysing the
        // next code point, otherwise skip the quotes in the 'url_string' and exit this block of code
        auto u_match = *position == 0x0055 || *position == 0x0075;
        ranges::advance(position, u_match);
        if (!u_match)
        {
            skip_quotes();
            break;
        }

        // if the current character at 'position' is a 'r' or 'R', then advance over it, and move onto analysing the
        // next code point, otherwise parse the current 'url_string'
        auto r_match = *position == 0x0052 || *position == 0x0072;
        ranges::advance(position, r_match);
        if (!r_match)
        {
            auto parsed_url = detail::miscellaneous_internals::parse_url(url_string, document);
            break_if(parsed_url.first.empty());
            url_record = parsed_url.second;
        }

        // if the current character at 'position' is a 'l' or 'L', then advance over it, and move onto analysing the
        // next code point, otherwise parse the current 'url_string'
        auto l_match = *position == 0x004c || *position == 0x006c;
        ranges::advance(position, l_match);
        if (!l_match)
        {
            auto parsed_url = detail::miscellaneous_internals::parse_url(url_string, document);
            break_if(parsed_url.first.empty());
            url_record = parsed_url.second;
        }

        // remove any whitespace, and if the current character at 'position' is a '=', then advance over it, parse the
        // current 'url_string'
        infra::detail::infra_string_internals::collect_ascii_whitespace(input, position);
        auto equal_match = *position == 0x003d;
        ranges::advance(position, equal_match);
        if (!equal_match)
        {
            auto parsed_url = detail::miscellaneous_internals::parse_url(url_string, document);
            break_if(parsed_url.first.empty());
            url_record = parsed_url.second;
        }
        infra::detail::infra_string_internals::collect_ascii_whitespace(input, position);

        // remove the quotes (current format is: URL="https://www.example.com), and exit the block of code
        skip_quotes();
        break;

    } while (position != input.end());

    document->m_will_declaratively_refresh = ext::boolean::TRUE();

    // TODO
}


auto html::detail::has_stylesheet_blocking_scripts(
        const dom::nodes::document* document)
        -> ext::boolean
{
    return document->m_script_blocking_style_sheet_counter > 0
            || document->m_browsing_context
            && document->m_browsing_context->container_document->m_script_blocking_style_sheet_counter > 0;
}


auto html::detail::has_no_stylesheet_blocking_scripts(
        const dom::nodes::document* document)
        -> ext::boolean
{
    return !has_stylesheet_blocking_scripts(document);
}


auto html::detail::allowed_to_use(
        dom::nodes::document* document,
        ext::string_view feature)
        -> ext::boolean
{
    using feature_t = permissions_policy::detail::feature_t;
    using enum permissions_policy::detail::inherited_policy_value_t;

    return_if(!document->m_browsing_context) ext::boolean::FALSE();
    return permissions_policy::detail::algorithm_internals::is_feature_enabled_in_document_for_origin(
            magic_enum::enum_cast<feature_t>(feature).value(),
            document,
            document->m_origin) == ENABLED;
}
