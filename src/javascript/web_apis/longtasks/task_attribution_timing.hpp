#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_TASK_ATTRIBUTION_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_TASK_ATTRIBUTION_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace longtasks {class task_attribution_timing;}

class longtasks::task_attribution_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(task_attribution_timing);
    task_attribution_timing() = default;

private js_properties:
    ext::property<ext::string> container_type;
    ext::property<ext::string> container_src;
    ext::property<ext::string> container_id;
    ext::property<ext::string> container_name;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_TASK_ATTRIBUTION_TIMING_HPP
