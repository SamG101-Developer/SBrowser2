#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CSP_SECURITY_POLICY_VIOLATION_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CSP_SECURITY_POLICY_VIOLATION_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"

#include "webappsec_csp/csp_violation_report_body_private.hpp"


DEFINE_PRIVATE_CLASS(webappsec::csp, security_policy_violation_event)
        : dom::events::event_private
        , webappsec::csp::csp_violation_report_body_private
{
    MAKE_QIMPL(security_policy_violation_event);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CSP_SECURITY_POLICY_VIOLATION_EVENT_PRIVATE_HPP
