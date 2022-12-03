#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "performance_timeline/performance_entry_private.hpp"

namespace dom::nodes {class event_target;}
namespace dom::events {class event;}


DEFINE_PRIVATE_CLASS(event_timing, performance_event_timing)
        : performance_timeline::performance_entry_private
{
    MAKE_QIMPL(performance_event_timing);

    dom::nodes::event_target* event_target = nullptr;
    dom::events::event* event = nullptr;

    hr_time::dom_high_res_time_stamp processing_start;
    hr_time::dom_high_res_time_stamp processing_end;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_PRIVATE_HPP
