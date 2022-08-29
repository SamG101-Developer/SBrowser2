#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP

#include "ext/keywords.hpp"
#include USE_INNER_TYPES(html)


namespace html::detail
{
    task_queue_t timer_task_source;
    task_queue_t dom_manipulation_task_source;
    task_queue_t user_interaction_task_source;
    task_queue_t networking_task_source;
    task_queue_t history_traversal_task_source;

    /* SERVICE_WORKERS */
    task_queue_t handle_fetch_task_source;
    task_queue_t handle_functional_event_task_source;

    /* BACKGROUND_TASKS */
    task_queue_t idle_task_source;

    /* CONTACT_PICKER */
    task_queue_t contact_picker_task_source;

    /* FILE_API */
    task_queue_t file_reading_task_source;

    /* GAMEPAD */
    task_queue_t gamepad_task_source;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP
