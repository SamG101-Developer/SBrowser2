#include "csp_internals.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "infra/detail/code_points_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"

#include <magic_enum.hpp>

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/take_while.hpp>


auto content_security_policy::detail::csp_internals::parse_csp(
        ext::string_view string,
        ext::string_view source,
        ext::string_view disposition)
        -> content_security_policy_t
{
    // create a new ContentSecurityPolicy, and assign the 'source' and 'disposition' attributes by casting the string
    // values to enum attributes of the respective types
    content_security_policy_t csp;
    csp.source = magic_enum::enum_cast<source_t>(source).value();
    csp.disposition = magic_enum::enum_cast<disposition_t>(disposition).value();

    // iterate over the 'string' of directives to be added to the ContentSecurityPolicy
    for (auto token: string | ranges::views::split_string(';'))
    {
        // the token has any leading and trailing whitespace removed from the string, and if the token is empty, or
        // isn't an ascii string (ie contains non-ascii characters), then continue the for-loop to the next token
        token = infra::detail::infra_string_internals::strip_leading_and_trailing_ascii_whitespace(token);
        continue_if(token.empty() || !infra::detail::infra_string_internals::is_ascii_string(string));

        // the directive name is the token upto the first occurrence of a space character, converted into lowercase,
        // and as a string type (has to have the string conversion after the ranges are used to manipulate it)
        auto raw_directive_name = infra::detail::infra_string_internals::collect_code_points_not_matching(token, token.begin(), ' ');
        auto directive_name = raw_directive_name
                | ranges::views::lowercase()
                | ranges::to<ext::string>();

        // if the ContentSecurityPolicy's directives already contain the 'directive_name', then continue the for-loop -
        // no duplicates are allowed
        continue_if(ranges::contains(csp.directive_set | ranges::views::keys, directive_name));

        // the 'directive_value' is the 'token' split on the spaces (the first string that was the directive name has
        // been automatically removed when teh code points upto the first space were collected
        auto directive_value = token | ranges::views::split_string(' ');
        csp.directive_set.emplace_back(directive_name, directive_value);
    }
}


auto content_security_policy::detail::csp_internals::parse_csp_list(
        ext::string_view string,
        ext::string_view source,
        ext::string_view disposition)
        -> ext::vector<content_security_policy_t*>
{
    // create an empty list of ContentSecurityPolicies that will be filled and returned by parsing
    // ContentSecurityPolicies individually
    ext::vector<content_security_policy_t*> content_security_policies {};

    // iterate through the 'string', split on commas
    for (auto token: string | ranges::views::split_string(','))
    {
        // create a ContentSecurityPolicy from the 'token', by parsing each 'token' with the 'parse_csp(...)' method;
        // continue the loop iteration if the created policy's 'directive_set' is empty ie it won't ave an effect on
        // anything
        auto policy = parse_csp(token, source, disposition);
        continue_if(policy.directive_set.empty());

        // save the address of the new ContentSecurityPolicy into the list
        content_security_policies.push_back(&policy);
    }

    // return the list of ContentSecurityPolicies
    return content_security_policies;
}
