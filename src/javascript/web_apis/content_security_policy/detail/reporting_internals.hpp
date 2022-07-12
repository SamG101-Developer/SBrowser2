#ifndef SBROWSER2_REPORTING_INTERNALS_HPP
#define SBROWSER2_REPORTING_INTERNALS_HPP


#include "ext/string.hpp"
#include "url/url.hpp"
namespace content_security_policy::detail::violation_internals {struct violation;}

namespace content_security_policy::detail::reporting_internals
{
    auto obtain_blocked_uri_of_violations_resource(
            ext::string_view violation_resource)
            -> ext::string;

    auto strip_url_for_violation_report(
            url::url_object& url)
            -> ext::string;

    auto report_violation(
            violation_internals::violation& violation_object)
            -> void;
}

#endif //SBROWSER2_REPORTING_INTERNALS_HPP
