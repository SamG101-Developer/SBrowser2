#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP

#include "ext/memory.ixx"
#include <thread>
#include INCLUDE_INNER_TYPES(html)


struct html::detail::task_queue_t
{
    ext::queue<task_t> queue;
    ext::boolean enabled;
    std::observer_ptr<std::thread::id> id;
};


namespace html::detail
{
    /* DOM -- HTML */
    task_queue_t timer_task_source;
    task_queue_t dom_manipulation_task_source;
    task_queue_t user_interaction_task_source;
    task_queue_t networking_task_source;
    task_queue_t history_traversal_task_source;
    task_queue_t canvas_blob_serialization_task_source;

    /* STORAGE */ // TODO : official?
    task_queue_t storage_task_source;

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

    /* GEOLOCATION */
    task_queue_t geolocation_task_source;

    /* PERMISSIONS */
    task_queue_t permissions_task_source;

    /* CLIPBOARD */
    task_queue_t clipboard_task_source;

    /* INTERSECTION_OBSERVER */
    task_queue_t intersection_observer_task_source;

    /* MEDIA_PROCESSOR */
    task_queue_t media_processor_task_source;

    /* [WEB-SOCKETS] */
    task_queue_t websocket_task_source;

    /* [MEDIASESSION] */
    task_queue_t media_session_task_source;

    /* [WEB-LOCKS] */
    task_queue_t web_locks_task_source;

    /* [SENSORS] */
    task_queue_t sensors_task_source;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_TASK_INTERNALS_HPP
