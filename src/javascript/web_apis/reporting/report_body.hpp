#pragma once
#ifndef SBROWSER2_REPORT_BODY_HPP
#define SBROWSER2_REPORT_BODY_HPP

#include "dom_object.hpp"
namespace reporting {class report_body;}


class reporting::report_body
        : public virtual web_apis::dom_object
{
public js_methods:
    auto to_json() const -> ext::string override;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_REPORT_BODY_HPP
