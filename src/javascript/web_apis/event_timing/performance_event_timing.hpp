#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace event_timing {class performance_event_timing;}

#include USE_INNER_TYPES(hr_time)
namespace dom::nodes {class event_target;}
namespace dom::events {class event;}


class event_timing::performance_event_timing
        : public performance_timeline::performance_entry
{
public constructors:
    performance_event_timing();

public js_properties:
    ext::property<hr_time::dom_high_res_time_stamp> processing_start;
    ext::property<hr_time::dom_high_res_time_stamp> processing_end;
    ext::property<ext::boolean> cancelable;
    ext::property<dom::nodes::node*> target;
    ext::property<ext::number<ulonglong>> interaction_id;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;

private cpp_properties:
    dom::nodes::event_target* m_event_target;
    dom::events::event* m_event;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(processing_start);
    DEFINE_CUSTOM_GETTER(processing_end);
    DEFINE_CUSTOM_GETTER(cancelable);
    DEFINE_CUSTOM_GETTER(target);
    DEFINE_CUSTOM_GETTER(interaction_id);
    DEFINE_CUSTOM_GETTER(name) override;
    DEFINE_CUSTOM_GETTER(entry_type) override;
    DEFINE_CUSTOM_GETTER(start_time) override;
    DEFINE_CUSTOM_GETTER(duration) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP
