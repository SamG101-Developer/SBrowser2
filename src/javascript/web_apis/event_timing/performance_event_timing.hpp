#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace event_timing {class performance_event_timing;}

#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class event_target;}
namespace dom::events {class event;}


class event_timing::performance_event_timing
        : public performance_timeline::performance_entry
{
public constructors:
    performance_event_timing();

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;

private cpp_properties:
    dom::nodes::event_target* m_event_target;
    dom::events::event* m_event;

private js_properties:
    DEFINE_GETTER(processing_start, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(processing_end, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(cancelable, ext::boolean);
    DEFINE_GETTER(target, dom::nodes::node*);
    DEFINE_GETTER(interaction_id, ext::number<ulonglong>);

    DEFINE_GETTER(name) override;
    DEFINE_GETTER(entry_type) override;
    DEFINE_GETTER(start_time) override;
    DEFINE_GETTER(duration) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP
