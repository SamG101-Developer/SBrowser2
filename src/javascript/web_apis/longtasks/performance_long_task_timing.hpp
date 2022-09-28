#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONG_TASK_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONG_TASK_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace longtasks {class performance_long_task_timing;}

#include "ext/vector.hpp"
namespace longtasks {class task_attribution_timing;}

#include "performance_long_task_timing_private.hpp"


class longtasks::performance_long_task_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_long_task_timing);
    MAKE_PIMPL(performance_long_task_timing);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(attribution, ext::vector_view<task_attribution_timing*>);

    DEFINE_GETTER(name, ext::string) override;
    DEFINE_GETTER(entry_type, ext::string) override {return "longtask";}
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LONGTASKS_PERFORMANCE_LONG_TASK_TIMING_HPP
