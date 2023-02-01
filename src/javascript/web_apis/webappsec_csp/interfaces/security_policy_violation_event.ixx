module;
#include "ext/macros.hpp"


export module apis.webappsec_csp.security_policy_violation_event;
import apis.dom.event;
import apis.webappsec_csp.csp_violation_report_body;


DEFINE_PUBLIC_CLASS(webappsec_csp, security_policy_violation_event) final
        : public dom::events::event
        , public csp_violation_report_body
{
public typedefs:
    using security_policy_t = ext::map<ext::string, ext::any>;

public constructors:
    security_policy_violation_event(ext::string_view event_type, security_policy_t&& event_init = {});
    MAKE_PIMPL(security_policy_violation_event);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
};
