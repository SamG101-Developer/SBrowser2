#pragma once
#ifndef SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP
#define SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP


#include "content_security_policy/violations/csp_violation_report_body.hpp"
#include "dom/events/event.hpp"
namespace content_security_policy::violations {class security_policy_violation_event;}

class content_security_policy::violations::security_policy_violation_event
        : public dom::events::event
        , public csp_violation_report_body
{
public constructors:
    security_policy_violation_event() = default;
    security_policy_violation_event(ext::string_view event_type, ext::string_any_map_view event_init = {});

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SECURITY_POLICY_VIOLATION_EVENT_HPP
