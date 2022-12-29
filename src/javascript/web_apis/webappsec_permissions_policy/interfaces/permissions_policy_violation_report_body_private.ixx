module;
#include "ext/macros/macros.hpp"


export module apis.webappsec_permissions_policy.permissions_policy_violation_report_body_private;
import apis.reporting.report_body_private;

import apis.webappsec_permissions_policy.types;
import ext.core;


DEFINE_PUBLIC_CLASS(webappsec_permissions_policy, permissions_policy_violation_report_body)
        : virtual reporting::report_body_private
{
public:
    MAKE_QIMPL(permissions_policy_violation_report_body);

public:
    ext::string feature_id;
    ext::string source_id;

    ext::number<long> line_number;
    ext::number<long> column_number;

    detail::disposition_t disposition;
};
