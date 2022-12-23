#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_DETAIL_PROCESSING_INTERNALS_HPP


#include INCLUDE_INNER_TYPES(background_tasks)
#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class window;}


namespace background_tasks::detail
{
    template <ext::callable F>
    auto start_idle_period(
            dom::nodes::window* window,
            F&& get_deadline)
            -> void;

    template <ext::callable F>
    auto invoke_idle_callbacks_algorithm(
            dom::nodes::window* window,
            F&& get_deadline)
            -> hr_time::dom_high_res_time_stamp;

    auto invoke_idle_callback_timeout_algorithm(
            ext::number<ulong> handle,
            dom::nodes::window* window)
            -> void;

    auto should_idle_period_be_delayed()
            -> ext::boolean;

    auto should_idle_period_end_early()
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_DETAIL_PROCESSING_INTERNALS_HPP
