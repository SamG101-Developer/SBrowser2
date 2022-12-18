module;
#include "ext/macros/pimpl.hpp"


export module apis.event_timing.performance_event_timing;
import apis.performance_timeline.performance_entry;
import apis.hr_time.types;


DEFINE_PRIVATE_CLASS(event_timing, performance_event_timing)
        : performance_timeline::performance_entry_private
{
    MAKE_QIMPL(performance_event_timing);

    dom::nodes::event_target* event_target = nullptr;
    dom::events::event* event = nullptr;

    hr_time::dom_high_res_time_stamp processing_start;
    hr_time::dom_high_res_time_stamp processing_end;
};
