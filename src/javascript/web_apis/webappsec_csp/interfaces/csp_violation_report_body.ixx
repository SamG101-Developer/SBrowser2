module;
#include "ext/macros.hpp"

export module apis.webappsec_csp.csp_violation_report_body;
import apis.reporting.report_body;


DEFINE_PUBLIC_CLASS(webappsec_csp, csp_violation_report_body) final
        : reporting::report_body
{
public constructors:
    csp_violation_report_body();
    MAKE_PIMPL(csp_violation_report_body);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(document_url, ext::string);
    DEFINE_GETTER(referrer, ext::string);
    DEFINE_GETTER(blocked_uri, ext::string);
    DEFINE_GETTER(effective_directive, ext::string);
    DEFINE_GETTER(original_policy, ext::string);
    DEFINE_GETTER(source_file, ext::string);
    DEFINE_GETTER(sample, ext::string);
    DEFINE_GETTER(disposition, detail::security_policy_violation_event_disposition_t);

    DEFINE_GETTER(status_code, ext::number<ushort>);
    DEFINE_GETTER(line_number, ext::number<ulong>);
    DEFINE_GETTER(column_number, ext::number<ulong>);
};
