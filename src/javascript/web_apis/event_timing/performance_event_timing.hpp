#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP

#include "performance_timeline/performance_entry.hpp"
namespace event_timing {class performance_event_timing;}

#include USE_INNER_TYPES(high_resolution_time)
namespace dom::nodes {class event_target;}
namespace dom::events {class event;}


class event_timing::performance_event_timing
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_event_timing);
    performance_event_timing() = default;

public js_properties:
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> processing_start;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> processing_end;
    ext::property<ext::boolean> cancelable;
    ext::property<dom::nodes::node*> target;
    ext::property<ext::number<ulonglong>> interaction_id;

public cpp_methods:
    auto to_json() const -> ext::string override;

private cpp_properties:
    dom::nodes::event_target* m_event_target;
    dom::events::event* m_event;

private cpp_accessors:
    DEFINE_GETTER(processing_start);
    DEFINE_GETTER(processing_end);
    DEFINE_GETTER(cancelable);
    DEFINE_GETTER(target);
    DEFINE_GETTER(interaction_id);
    DEFINE_GETTER(name) override;
    DEFINE_GETTER(entry_type) override;
    DEFINE_GETTER(start_time) override;
    DEFINE_GETTER(duration) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_PERFORMANCE_EVENT_TIMING_HPP