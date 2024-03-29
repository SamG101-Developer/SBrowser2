module;
#include "ext/macros.hpp"


export module apis.event_timing.performance_event_timing:p;
import apis.performance_timeline.performance_entry;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(hr_time);


DEFINE_PRIVATE_CLASS(event_timing, performance_event_timing)
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(performance_event_timing);

public:
    std::observer_ptr<dom::event_target> event_target = nullptr;
    std::observer_ptr<dom::event> event = nullptr;

    hr_time::dom_high_res_time_stamp processing_start;
    hr_time::dom_high_res_time_stamp processing_end;
};
