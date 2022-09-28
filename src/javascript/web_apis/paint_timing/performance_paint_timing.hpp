#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_PERFORMANCE_PAINT_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_PERFORMANCE_PAINT_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace paint_timing {class performance_paint_timing;}

#include "performance_paint_timing_private.hpp"


class paint_timing::performance_paint_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_paint_timing);
    MAKE_PIMPL(performance_paint_timing);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(name, ext::string) override {return "paint";}
    DEFINE_GETTER(entry_type, ext::string) override {return "first-paint";} // TODO
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override {return 0;};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_PERFORMANCE_PAINT_TIMING_HPP
