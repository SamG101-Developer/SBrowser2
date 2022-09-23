#pragma once
#ifndef SBROWSER2_REPORT_HPP
#define SBROWSER2_REPORT_HPP

#include "dom_object.hpp"
namespace reporting {class report;}

namespace reporting {class report_body;}


class reporting::report
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(report);
    report() = default;

private js_properties:
    ext::property<ext::string> type;
    ext::property<ext::string> url;
    ext::property<std::unique_ptr<report_body>> body;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;
};


#endif //SBROWSER2_REPORT_HPP
