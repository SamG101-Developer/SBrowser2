#pragma once
#ifndef SBROWSER2_PERMISSIONS_POLICY_VIOLATION_REPORT_BODY_HPP
#define SBROWSER2_PERMISSIONS_POLICY_VIOLATION_REPORT_BODY_HPP

#include "reporting/report.hpp"
namespace permissions_policy {class permissions_policy_violation_report_body;}


class permissions_policy::permissions_policy_violation_report_body
        : public reporting::report
{
public js_properties:
    ext::property<ext::string> feature_id;
    ext::property<ext::string> source_file;
    ext::property<ext::string> disposition;
    ext::property<ext::number<long>> line_number;
    ext::property<ext::number<long>> column_number;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_PERMISSIONS_POLICY_VIOLATION_REPORT_BODY_HPP
