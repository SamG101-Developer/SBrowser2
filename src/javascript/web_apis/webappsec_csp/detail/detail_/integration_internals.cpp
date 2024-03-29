#include "integration_internals.hpp"
#include "directive_internals.hpp"





#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "html/detail/policy_internals.hpp"
#include "webappsec_csp/_typedefs.hpp"
#include "webappsec_csp/detail/csp_internals.hpp"


auto webappsec::detail::report_content_security_policy_violations(
        const fetch::detail::request_t& request)
        -> void
{
    using enum ranges::filter_compare_t;

    // For each policy whose disposition is not ENFORCED, and is violated by the request, create a violation object, and
    // report the violation (only reported policies are used to report any violations).
    for (decltype(auto) policy: ext::get<1>(request.policy_container)->csp_list
            | ranges::views::filter_eq<NE>(&policy_t::disposition, disposition_t::ENFORCE, ext::underlying)
            | ranges::views::filter([&request](auto* policy) {return does_request_violate_policy(request, *policy);}))
    {
        auto violation = create_violation_object(request, *policy);
        report_violation(std::move(violation));
    }
}


auto webappsec::detail::should_request_be_blocked_by_content_security_policy(
        const fetch::detail::request_t& request)
        -> should_t
{
    // Get the content security policy from the request's policy container. Default the result to false (request isn't
    // blocked by default)
    using enum ranges::filter_compare_t;
    auto result = should_t::ALLOWED;

    // For each policy whose disposition is not REPORT, and is violated by the request, create a violation object, and
    // report the violation (Only enforced policies are used to check if a request should be blocked).
    for (decltype(auto) policy: ext::get<1>(request.policy_container)->csp_list
            | ranges::views::filter_eq<NE>(&policy_t::disposition, disposition_t::REPORT, ext::underlying)
            | ranges::views::filter([&request](auto* policy) {return does_request_violate_policy(request, *policy);}))
    {
        auto violation = create_violation_object(request, *policy);
        report_violation(std::move(violation));
        result = should_t::BLOCKED;
    }

    // Return if the request should be blocked or not.
    return result;
}


auto webappsec::detail::should_response_to_request_be_blocked_by_content_security_policy(
        const fetch::detail::response_t& response,
        const fetch::detail::request_t& request)
        -> should_t
{
    // Get the content security policy from the request's policy container. Default the result to false (response isn't
    // blocked by default)
    using enum ranges::views::filter_compare_t;
    decltype(auto) csp_list = request.policy_container->csp_list;
    auto result = ext::boolean::FALSE_();

    // For each policy, iterate over its directives that are blocked by the 'post_request_check'
    for (decltype(auto) policy: csp_list)
    {
        auto directive_post_request_check =
                [&request, &response, policy](directive_t* directive)
                {return post_request_check(*directive, request, response, *policy);};

        // Create and report violations for each policy, and set the result to true if the policy is being enforced.
        for (decltype(auto) directive: policy->directive_set | ranges::views::filter(directive_post_request_check))
        {
            auto violation = create_violation_object(request, *policy);
            report_violation(std::move(violation));
            result = policy->disposition == disposition_t::ENFORCE ? result : ext::boolean::TRUE_();
        }
    }

    // Return if the response should be blocked or not.
    return result;
}
