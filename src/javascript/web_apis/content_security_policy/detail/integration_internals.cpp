#include "integration_internals.hpp"

#include USE_INNER_TYPES(content_security_policy)

#include "ext/ranges.hpp"

#include "content_security_policy/detail/reporting_internals.hpp"
#include "content_security_policy/detail/violation_internals.hpp"

#include "fetch/detail/request_internals.hpp"
#include "html/detail/policy_internals.hpp"


auto content_security_policy::detail::report_content_security_policy_violations(
        const fetch::detail::request_t& request)
        -> void
{
    using enum ranges::views::filter_compare_t;
    decltype(auto) csp_list = request.policy_container->csp_list;

    for (decltype(auto) policy: csp_list
            | ranges::views::filter_eq<EQ>(&content_security_policy_t::disposition, disposition_t::ENFORCE, ext::identity{})
            | ranges::views::filter([&request](auto* policy) {return does_request_violate_policy(request, *policy);}))
    {
        auto violation = create_violation_object(request, *policy);
        report_violation(violation);
    }
}
