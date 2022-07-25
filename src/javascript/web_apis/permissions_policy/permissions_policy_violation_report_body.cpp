#include "permissions_policy_violation_report_body.hpp"


auto permissions_policy::permissions_policy_violation_report_body::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<permissions_policy_violation_report_body>{isolate}
        .inherit<dom_object>()
        .var("featureId", &permissions_policy_violation_report_body::feature_id, true)
        .var("sourceFile", &permissions_policy_violation_report_body::source_file, true)
        .var("disposition", &permissions_policy_violation_report_body::disposition, true)
        .var("lineNumber", &permissions_policy_violation_report_body::line_number, true)
        .var("columnNumber", &permissions_policy_violation_report_body::column_number, true)
        .auto_wrap_objects();
}