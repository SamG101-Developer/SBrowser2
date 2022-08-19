#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONGTASK_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONGTASK_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace longtasks {class performance_longtask_timing;}

#include "ext/vector.hpp"
namespace longtasks {class task_attribution_timing;}


class longtasks::performance_longtask_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_longtask_timing);
    performance_longtask_timing() = default;

public js_properties:
    ext::property<const ext::vector<task_attribution_timing*>> attribution;

public cpp_methods:
    auto to_json() const -> ext::string override;

private cpp_accessors:
    // TODO (inherited properties)
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONGTASK_TIMING_HPP
