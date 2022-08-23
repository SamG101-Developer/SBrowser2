#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/concepts.hpp"
#include USE_INNER_TYPES(high_resolution_time)
namespace dom::nodes {class window;}


namespace background_tasks::detail
{
    template <callable F>
    auto start_idle_period(
            dom::nodes::window* window,
            F&& get_deadline)
            -> void;

    template <callable F>
    auto invoke_idle_callbacks_algorithm(
            dom::nodes::window* window,
            F&& get_deadline)
            -> high_resolution_time::detail::dom_high_res_time_stamp_t;

    auto invoke_idle_callback_timeout_algorithm(
            dom::nodes::window* window)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BACKGROUND_TASKS_DETAIL_PROCESSING_INTERNALS_HPP
