#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CSP_CSP_VIOLATION_REPORT_BODY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CSP_CSP_VIOLATION_REPORT_BODY_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "reporting/report_body_private.hpp"

#include INCLUDE_INNER_TYPES(webappsec_csp)
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(webappsec::csp, csp_violation_report_body) : reporting::report_body_private
{
    MAKE_QIMPL(csp_violation_report_body);

    ext::string report_type = u"csp-violation";
    std::unique_ptr<detail::violation_t> violation;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CSP_CSP_VIOLATION_REPORT_BODY_PRIVATE_HPP
