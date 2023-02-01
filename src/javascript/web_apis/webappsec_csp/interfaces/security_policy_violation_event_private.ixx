module;
#include "ext/macros.hpp"


export module apis.webappsec_csp.security_policy_violation_event:p;
import apis.dom.event;
import apis.webappsec_csp.csp_violation_report_body


DEFINE_PRIVATE_CLASS(webappsec::csp, security_policy_violation_event)
        : dom::events::event_private
        , webappsec_csp::csp_violation_report_body_private
{
public:
    MAKE_QIMPL(security_policy_violation_event);
};
