#pragma once
#ifndef SBROWSER2_PERFORMANCE_HPP
#define SBROWSER2_PERFORMANCE_HPP

#include "dom/nodes/event_target.hpp"
namespace hr_time {class performance;}
namespace hr_time {class performance_private;}

#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(user_timing)
namespace performance_timeline {class performance_entry;}
namespace event_timing {class event_counts;}
namespace event_timing {class interaction_counts;}
namespace user_timing {class performance_mark;}
namespace user_timing {class performance_measure;}


class hr_time::performance
        : public dom::nodes::event_target
{
public constructors:
    performance();
    MAKE_PIMPL(performance);
    MAKE_V8_AVAILABLE;

public js_methods:
    /* [HR-TIME] */
    auto now() const -> dom_high_res_time_stamp;

    /* [PERFORMANCE-TIMELINE] */
    auto get_entries() -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_type(ext::string_view type) -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_name(ext::string_view name, ext::string_view type = u"") -> ext::vector<performance_timeline::performance_entry*>;

    /* [RESOURCE-TIMING] */
    auto clear_resource_timings() -> void;
    auto set_resource_timing_buffer_size(ext::number<ulong> max_size) -> void;

    /* [USER-TIMING] */
    auto mark(ext::string&& mark_name, user_timing::detail::performance_mark_options_t&& mar_options = {}) -> user_timing::performance_mark;
    auto measure(ext::string&& measure_name, user_timing::detail::performance_measure_options_t&& measure_options = {}) -> user_timing::performance_measure;
    auto measure(ext::string&& measure_name, ext::string&& mark_start, ext::string&& mark_end) -> user_timing::performance_measure;
    auto clear_marks(ext::string&& mark_name) -> void;
    auto clear_measures(ext::string&& measure_name) -> void;

private js_properties:
    /* [HR-TIME] */
    DEFINE_GETTER(time_origin, ext::number<double>);

    /* [EVENT-TIMING] */
    DEFINE_GETTER(event_counts, const event_timing::event_counts*);
    DEFINE_GETTER(interaction_counts, const event_timing::interaction_counts*);
};


// TODO : `ext::property<Performance> performance` in `WindowOrWorkerGlobalScope`


#endif //SBROWSER2_PERFORMANCE_HPP
