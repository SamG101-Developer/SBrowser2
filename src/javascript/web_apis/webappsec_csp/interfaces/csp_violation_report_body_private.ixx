module;
#include "ext/macros.hpp"


export module apis.webappsec_csp.csp_violation_report_body:p;
import apis.reporting.report_body;


DEFINE_PRIVATE_CLASS(webappsec_csp, csp_violation_report_body)
        : reporting::report_body_private
{
public:
    MAKE_QIMPL(csp_violation_report_body);

public:
    ext::string report_type = u"csp-violation";
    std::unique_ptr<detail::violation_t> violation;
};
