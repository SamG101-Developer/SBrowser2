module;
#include "ext/macros/macros.hpp"


export module apis.dom.window_private;
import apis.dom.event_target_private;
import apis.background_tasks.types;

import apis.dom.types;
import apis.html.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, window)
        : dom::event_target_private
{
    MAKE_QIMPL(window);

    /* [HTML] */
    ext::boolean has_dispatched_scroll_event = false;
    std::unique_ptr<detail::custom_element_reactions_stack_t> custom_element_reaction_stack;
    ext::queue<element*> current_element_queue;
    hr_time::dom_high_res_time_stamp last_activation_timestamp;
    html::detail::cross_origin_property_descriptor_map_t cross_origin_property_descriptor_map;

    std::unique_ptr<html::detail::navigable_t> navigable;
    std::unique_ptr<document> document;
    std::unique_ptr<html::other::location> location;
    std::unique_ptr<html::other::custom_element_registry> custom_elements;
    std::unique_ptr<html::navigators::navigator> navigator;

    /* [BACKGROUND-TASKS] */
    ext::vector<background_tasks::detail::idle_request_callback_t> idle_request_callbacks;
    ext::vector<background_tasks::detail::idle_request_callback_t> runnable_idle_callbacks;
    ext::number<ulong> idle_callback_identifier;

    template <ext::callable F> auto start_idle_period(F&& get_deadline) -> hr_time::dom_high_res_time_stamp;
    template <ext::callable F> auto invoke_idle_callbacks(F&& get_deadline) -> hr_time::dom_high_res_time_stamp;
    auto invoke_idle_callback_timeout() -> void;

    /* [EVENT-TIMING] */
    ext::vector<event_timing::performance_event_timing*> entries_to_be_queued;
    std::unique_ptr<event_timing::performance_event_timing> pending_first_pointer_down;
    ext::boolean has_dispatched_input_event;
    ext::number<short> user_interaction_value = ext::number<int>::random(100, 10000);
    ext::map<ext::number<int>, event_timing::performance_event_timing*> pending_key_downs;
    ext::map<ext::number<int>, event_timing::performance_event_timing*> pending_pointer_downs;
    ext::map<ext::number<int>, ext::number<int>> pointer_interaction_value_map;
    ext::set<ext::number<int>> pointer_is_drag_set;
    std::unique_ptr<event_timing::event_counts> event_counts;
    std::unique_ptr<event_timing::interaction_counts> interaction_counts;
};
