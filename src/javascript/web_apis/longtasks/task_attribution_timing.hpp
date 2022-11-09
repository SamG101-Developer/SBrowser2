#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_TASK_ATTRIBUTION_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_TASK_ATTRIBUTION_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace longtasks {class task_attribution_timing;}

#include "task_attribution_timing_private.hpp"

class longtasks::task_attribution_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(task_attribution_timing);
    MAKE_PIMPL(task_attribution_timing);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(container_type, ext::string);
    DEFINE_GETTER(container_src, ext::string);
    DEFINE_GETTER(container_id, ext::string);
    DEFINE_GETTER(container_name, ext::string);

    DEFINE_GETTER(name, ext::string) override {return u"unknown";}
    DEFINE_GETTER(entry_type, ext::string) override {return u"taskattribution";}
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override {return 0;}
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override {return 0;}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_TASK_ATTRIBUTION_TIMING_HPP
