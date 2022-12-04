#ifndef SBROWSER2_REPORTING_INTERNALS_HPP
#define SBROWSER2_REPORTING_INTERNALS_HPP


#include INCLUDE_INNER_TYPES(webappsec_csp)
#include INCLUDE_INNER_TYPES(url)


namespace webappsec::detail
{
    auto obtain_blocked_uri_of_violations_resource(
            ext::string_view violation_resource)
            -> ext::string;

    auto strip_url_for_violation_report(
            url::detail::url_t& url)
            -> ext::string;

    auto report_violation(
            violation_t& violation)
            -> void;
}

#endif //SBROWSER2_REPORTING_INTERNALS_HPP
