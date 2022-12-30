module;
#include "ext/macros.hpp"


module apis.webappsec_permissions_policy.permissions_policy_violation_report_body;
import apis.webappsec_permissions_policy.types;

import apis.reporting.report_body;

import ext.core;
import js.env.module_type;


auto webappsec_permissions_policy::permissions_policy_violation_report_body::get_feature_id() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->feature_id;
}


auto webappsec_permissions_policy::permissions_policy_violation_report_body::get_source_file() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->source_file;
}


auto webappsec_permissions_policy::permissions_policy_violation_report_body::get_line_number() const -> ext::number<long>
{
    ACCESS_PIMPL;
    return d->line_number;
}


auto webappsec_permissions_policy::permissions_policy_violation_report_body::get_column_number() const -> ext::number<long>
{
    ACCESS_PIMPL;
    return d->column_number;
}


auto webappsec_permissions_policy::permissions_policy_violation_report_body::get_disposition() const -> detail::disposition_t
{
    ACCESS_PIMPL;
    return d->disposition;
}


auto webappsec_permissions_policy::permissions_policy_violation_report_body::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<reporting::report_body>()
        .property("featureId", &permissions_policy_violation_report_body::get_feature_id)
        .property("sourceFile", &permissions_policy_violation_report_body::get_source_file)
        .property("disposition", &permissions_policy_violation_report_body::get_disposition)
        .property("lineNumber", &permissions_policy_violation_report_body::get_line_number)
        .property("columnNumber", &permissions_policy_violation_report_body::get_column_number)
        .auto_wrap_objects();
    
    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}