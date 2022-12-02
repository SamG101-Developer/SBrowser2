#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_DETAIL_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_DETAIL_TIMING_INTERNALS_HPP

#include "ext/boolean.ixx"
#include INCLUDE_INNER_TYPES(event_timing)
#include INCLUDE_INNER_TYPES(hr_time)

namespace dom::events {class event;}
namespace dom::nodes {class event_target;}
namespace dom::nodes {class document;}
namespace dom::nodes {class window;}
namespace event_timing {class performance_event_timing;}


namespace event_timing::detail
{
    auto should_event_be_considered_for_event_timing(
            dom::events::event* event)
            -> ext::boolean;

    auto should_add_performance_event_timing(
            performance_event_timing* entry,
            performance_observer_init_t&& options)
            -> ext::boolean;

    auto increase_interaction_count(
            dom::nodes::window* window,
            ext::string&& type)
            -> void;

    auto compute_interaction_id(
            dom::events::event* event)
            -> ext::number<int>;

    auto initialize_event_timing(
            dom::events::event* event,
            ext::number<double> processing_start,
            ext::number<int> interaction_id)
            -> std::unique_ptr<performance_event_timing>;

    auto finalize_event_timing(
            performance_event_timing* timing_entry,
            dom::events::event* event,
            dom::nodes::event_target* target,
            ext::number<double> processing_end)
            -> void;

    auto dispatch_pending_event_timing_entries(
            dom::nodes::document* document)
            -> void;

    auto set_event_timing_entry_duration(
            performance_event_timing* timing_entry,
            dom::nodes::window* window,
            hr_time::dom_high_res_time_stamp rendering_timestamp)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EVENT_TIMING_DETAIL_TIMING_INTERNALS_HPP
