#ifndef SBROWSER2_WINDOW_HPP
#define SBROWSER2_WINDOW_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class window;}

#include USE_INNER_TYPES(background_tasks)
namespace background_tasks {class idle_deadline;}
namespace dom::nodes {class document;}


class dom::nodes::window final
        : public event_target
{
public js_properties:
    /* HTML */
    ext::property<std::unique_ptr<document>> document;

    /* BACKGROUND_TASKS */
    auto request_idle_callback(
            background_tasks::detail::idle_request_callback_t&& callback,
            background_tasks::detail::idle_request_options_t&& options)
            -> ext::number<ulong>;

    auto cancel_idle_task(
            const ext::number<ulong>& handle)
            -> void;

private cpp_properties:
    /* HTML */
    ext::boolean m_has_dispatched_scroll_event = false;

    /* BACKGROUND_TASKS */
    ext::vector<background_tasks::idle_deadline*> m_idle_request_callbacks;
    ext::vector<background_tasks::idle_deadline*> m_runnable_idle_callbacks;
    ext::number<size_t> m_idle_callback_identifier;
};


#endif //SBROWSER2_WINDOW_HPP
