#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_PERFORMANCE_PAINT_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_PERFORMANCE_PAINT_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace paint_timing {class performance_paint_timing;}


class paint_timing::performance_paint_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_paint_timing);
    performance_paint_timing();

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(name) override;
    DEFINE_CUSTOM_GETTER(entry_type) override;
    DEFINE_CUSTOM_GETTER(start_time) override;
    DEFINE_CUSTOM_GETTER(duration) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAINT_TIMING_PERFORMANCE_PAINT_TIMING_HPP
