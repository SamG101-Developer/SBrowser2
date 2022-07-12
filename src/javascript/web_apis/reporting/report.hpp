#pragma once
#ifndef SBROWSER2_REPORT_HPP
#define SBROWSER2_REPORT_HPP

#include "dom_object.hpp"
namespace reporting {class report;}

namespace reporting {class report_body;}


class reporting::report
        : public virtual web_apis::dom_object
{
public js_methods:
    auto to_json() const -> ext::string override;

public js_properties:
    ext::property<ext::string> type;
    ext::property<ext::string> url;
    ext::property<std::unique_ptr<report_body>> body;
};


#endif //SBROWSER2_REPORT_HPP
