#pragma once
#ifndef SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP
#define SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP

#include "dom/events/event.hpp"
#include "webappsec_csp/csp_violation_report_body.hpp"
namespace webappsec::csp {class security_policy_violation_event;}


class webappsec::csp::security_policy_violation_event
        : public dom::events::event
        , public csp_violation_report_body
{
public constructors:
    DOM_CTORS(security_policy_violation_event);
    security_policy_violation_event() = default;
    security_policy_violation_event(ext::string_view event_type, ext::map<ext::string, ext::any> event_init = {});

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP
