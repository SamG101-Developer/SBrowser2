module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.webappsec_permissions_policy.permissions_policy_violation_report_body;
import apis.reporting.report_body;

import apis.webappsec_permissions_policy.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(webappsec_permissions_policy, permissions_policy_violation_report_body) final
        : public reporting::report_body
{
public constructors:
    permissions_policy_violation_report_body();
    MAKE_PIMPL(permissions_policy_violation_report_body);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(feature_id, ext::string_view);
    DEFINE_GETTER(source_file, ext::string_view);
    DEFINE_GETTER(line_number, ext::number<long>);
    DEFINE_GETTER(column_number, ext::number<long>);
    DEFINE_GETTER(disposition, detail::disposition_t);
};
