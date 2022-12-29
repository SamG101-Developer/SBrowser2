module;
#include "ext/macros/pimpl.hpp"
#include <memory>


export module apis.event_timing.detail;
import apis.event_timing.types;
import apis.hr_time.types;

import apis.dom.types;
import apis.event_timing.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(event_timing)
{
    auto should_event_be_considered_for_event_timing(dom::event* event) -> ext::boolean;
    auto should_add_performance_event_timing(performance_event_timing* entry, performance_observer_init_t&& options) -> ext::boolean;
    auto increase_interaction_count(dom::window* window, ext::string&& type) -> void;
    auto compute_interaction_id(dom::event* event) -> ext::number<int>;
    auto initialize_event_timing(dom::event* event, ext::number<double> processing_start, ext::number<int> interaction_id) -> std::unique_ptr<performance_event_timing>;
    auto finalize_event_timing(performance_event_timing* timing_entry, dom::event* event, dom::event_target* target, ext::number<double> processing_end) -> void;
    auto dispatch_pending_event_timing_entries(dom::document* document) -> void;
    auto set_event_timing_entry_duration(performance_event_timing* timing_entry, dom::window* window, hr_time::dom_high_res_time_stamp rendering_timestamp) -> void;
};
