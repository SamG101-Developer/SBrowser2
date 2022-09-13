#pragma once
#ifndef SBROWSER2_CSP_VIOLATION_REPORT_BODY_HPP
#define SBROWSER2_CSP_VIOLATION_REPORT_BODY_HPP

#include "reporting/report_body.hpp"
namespace webappsec::csp {class csp_violation_report_body;}


class webappsec::csp::csp_violation_report_body
        : reporting::report_body
{
public constructors:
    DOM_CTORS(csp_violation_report_body);

public js_properties:
    ext::property<ext::string> document_url;
    ext::property<ext::string> referrer;
    ext::property<ext::string> blocked_url;
    ext::property<ext::string> effective_directive;
    ext::property<ext::string> original_policy;
    ext::property<ext::string> source_file;
    ext::property<ext::string> sample;
    ext::property<ext::string> disposition;

    ext::property<ext::number<ushort>> status_code;
    ext::property<ext::number<ulong>> line_number;
    ext::property<ext::number<ulong>> column_number;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_CSP_VIOLATION_REPORT_BODY_HPP
