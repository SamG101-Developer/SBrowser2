#ifndef SBROWSER2_REPORTING_INTERNALS_HPP
#define SBROWSER2_REPORTING_INTERNALS_HPP

#include "ext/string.hpp"
#include USE_INNER_TYPES(content_security_policy)
#include USE_INNER_TYPES(url)


namespace content_security_policy::detail
{
    auto obtain_blocked_uri_of_violations_resource(
            ext::string_view violation_resource)
            -> ext::string;

    auto strip_url_for_violation_report(
            url::detail::url_t& url)
            -> ext::string;

    auto report_violation(
            const violation_t& violation_object)
            -> void;
}

#endif //SBROWSER2_REPORTING_INTERNALS_HPP
