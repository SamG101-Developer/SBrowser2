#pragma once
#ifndef SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP
#define SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP

#include "dom/events/event.hpp"
#include "webappsec_csp/csp_violation_report_body.hpp"
namespace webappsec::csp {class security_policy_violation_event;}
namespace webappsec::csp {class security_policy_violation_event_private;}


class webappsec::csp::security_policy_violation_event
        : public dom::events::event
        , public csp_violation_report_body
{
public constructors:
    security_policy_violation_event(ext::string_view event_type, ext::map<ext::string, ext::any> event_init = {});
    MAKE_PIMPL(security_policy_violation_event);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP
