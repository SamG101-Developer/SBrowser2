#include "csp_internals.hpp"

#include "ext/functional.ixx"
#include "ext/ranges.hpp"

#include "fetch/detail/header_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "infra/detail/code_points_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"

#include "html/detail/origin_internals.hpp"
#include "url/detail/url_internals.hpp"
#include "webappsec_csp/_typedefs.hpp"

#include <magic_enum.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/take_while.hpp>


auto webappsec::detail::contains_header_delivered_csp(
        ext::vector_span<policy_t*> csp_list)
        -> ext::boolean
{
    return ranges::any_of(csp_list, source_t::HEADER, &policy_t::source);
}


auto webappsec::detail::serialize_csp_list(
        ext::vector_span<policy_t*> csp_list)
        -> ext::string
{
    return csp_list
            | ranges::views::transform(&serialize_csp, ext::deref)
            | ranges::to<ext::string>();
}


auto webappsec::detail::parse_csp(
        ext::string_view string,
        source_t source,
        disposition_t disposition)
        -> std::unique_ptr<policy_t>
{
    // create a new ContentSecurityPolicy, and assign the 'source' and 'disposition' attributes by casting the string
    // values to enum attributes of the respective types
    auto csp = std::make_unique<policy_t>();
    csp->source = source;
    csp->disposition = disposition;

    // iterate over the 'string' of directives to be added to the ContentSecurityPolicy
    for (auto token: string | ranges::views::split_string(u';'))
    {
        // the token has any leading and trailing whitespace removed from the string, and if the token is empty, or
        // isn't an ascii string (ie contains non-ascii characters), then continue the for-loop to the next token
        token = infra::detail::strip_leading_and_trailing_ascii_whitespace(token);
        continue_if(token.empty() || !infra::detail::is_ascii_string(string));

        // the directive name is the token upto the first occurrence of a space character, converted into lowercase,
        // and as a string type (has to have the string conversion after the ranges are used to manipulate it)
        auto raw_directive_name = infra::detail::collect_code_points_not_matching(token, token.begin(), ' ');
        auto directive_name = raw_directive_name
                | ranges::views::lowercase
                | ranges::to<ext::string>();

        // if the ContentSecurityPolicy's directives already contain the 'directive_name', then continue the for-loop -
        // no duplicates are allowed
        continue_if(ranges::contains(csp->directive_set | ranges::views::keys, directive_name));

        // the 'directive_value' is the 'token' split on the spaces (the first string that was the directive name has
        // been automatically removed when teh code points upto the first space were collected
        auto directive_value = token | ranges::views::split_string(' ');
        csp->directive_set.emplace_back(directive_name, directive_value);
    }
}


auto webappsec::detail::parse_csp_list(
        ext::string_view string,
        source_t source,
        disposition_t disposition)
        -> ext::vector<std::unique_ptr<policy_t>>
{
    // create an empty list of ContentSecurityPolicies that will be filled and returned by parsing
    // ContentSecurityPolicies individually
    auto content_security_policies = ext::vector<std::unique_ptr<policy_t>>{};

    // iterate through the 'string', split on commas
    for (auto token: string | ranges::views::split_string(u','))
    {
        // create a ContentSecurityPolicy from the 'token', by parsing each 'token' with the 'parse_csp(...)' method;
        // continue the loop iteration if the created policy's 'directive_set' is empty ie it won't ave an effect on
        // anything
        auto policy = parse_csp(token, source, disposition);
        continue_if(policy.directive_set.empty());

        // save the address of the new ContentSecurityPolicy into the list
        content_security_policies.push_back(std::move(policy));
    }

    // return the list of ContentSecurityPolicies
    return content_security_policies;
}


auto webappsec::detail::parse_responses_csp(
        const fetch::detail::response_t& response)
        -> ext::vector<std::unique_ptr<policy_t>>
{
    auto policies_1 = parse_csp_list(fetch::detail::extract_header_list_values(u"Content-Security-Policy", response.header_list), source_t::HEADER, disposition_t::ENFORCE);
    auto policies_2 = parse_csp_list(fetch::detail::extract_header_list_values(u"Content-Security-Policy-Report-Only", response.header_list), source_t::HEADER, disposition_t::REPORT);
    auto policies = ranges::views::concat(policies_1, policies_2);

    policies | ranges::views::for_each([&response](policy_t* policy) {policy->self_origin = url::detail::origin(response.url());});
    return policies | ranges::to<ext::vector<std::unique_ptr<policy_t>>>();
}
