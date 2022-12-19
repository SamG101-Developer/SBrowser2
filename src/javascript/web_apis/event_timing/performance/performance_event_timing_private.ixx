module;
#include "ext/macros/pimpl.hpp"


export module apis.event_timing.performance_event_timing_private;
import apis.performance_timeline.performance_entry_private;
import apis.hr_time.types;

import ext.memory;

namespace dom {class event;}
namespace dom {class event_target;}


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
