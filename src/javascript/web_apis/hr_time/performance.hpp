#pragma once
#ifndef SBROWSER2_PERFORMANCE_HPP
#define SBROWSER2_PERFORMANCE_HPP

#include "dom/nodes/event_target.hpp"
namespace hr_time {class performance;}

#include INCLUDE_INNER_TYPES(hr_time)
namespace performance_timeline {class performance_entry;}
namespace event_timing {class event_counts;}
namespace event_timing {class interaction_counts;}

#include "performance_private.hpp"


class hr_time::performance
        : public dom::nodes::event_target
{
public constructors:
    MAKE_PIMPL(performance);
    performance();
    MAKE_V8_AVAILABLE;

public js_methods:
    /* HIGH_RESOLUTION_TIME */
    auto now() -> dom_high_res_time_stamp;

    /* PERFORMANCE_TIMELINE */
    auto get_entries() -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_type(ext::string_view type) -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_name(ext::string_view name, ext::string_view type = "") -> ext::vector<performance_timeline::performance_entry*>;

    /* RESOURCE_TIMING */
    auto clear_resource_timings() -> void;
    auto set_resource_timing_buffer_size(ext::number<ulong> max_size) -> void;

private js_properties:
    /* HIGH_RESOLUTION_TIME */
    DEFINE_GETTER(time_origin, ext::number<double>);

    /* EVENT_TIMING */
    DEFINE_GETTER(event_counts, const event_timing::event_counts*);
    DEFINE_GETTER(interaction_counts, const event_timing::interaction_counts*);
};


// TODO : `ext::property<Performance> performance` in `WindowOrWorkerGlobalScope`


#endif //SBROWSER2_PERFORMANCE_HPP
