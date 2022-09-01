#ifndef SBROWSER2_WINDOW_HPP
#define SBROWSER2_WINDOW_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class window;}

#include <condition_variable>
#include <mutex>
#include <thread>
#include "ext/type_traits.hpp"
#include "ext/queue.hpp"
#include USE_INNER_TYPES(background_tasks)
#include USE_INNER_TYPES(dom)
namespace background_tasks {class idle_deadline;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace html::other {class navigator;}
namespace selection {class selection;}


class dom::nodes::window final
        : public event_target
{
public js_properties:
    /* HTML */
    ext::property<std::unique_ptr<document>> document;
    ext::property<std::unique_ptr<html::other::navigator>> navigator;

public js_methods:
    /* BACKGROUND_TASKS */
    auto request_idle_callback(
            background_tasks::detail::idle_request_callback_t&& callback,
            background_tasks::detail::idle_request_options_t&& options)
            -> ext::number<ulong>;

    auto cancel_idle_task(
            const ext::number<ulong>& handle)
            -> void;

    /* SELECTION */
    auto get_selection() -> selection::selection*;

private cpp_properties:
    /* HTML */
    ext::boolean m_has_dispatched_scroll_event = false;
    std::unique_ptr<dom::detail::custom_element_reactions_stack_t> m_custom_element_reaction_stack;
    ext::queue<dom::nodes::element*>* m_current_element_queue;

    /* BACKGROUND_TASKS */
    ext::vector<background_tasks::detail::idle_request_callback_t> m_idle_request_callbacks;
    ext::vector<background_tasks::detail::idle_request_callback_t> m_runnable_idle_callbacks;
    ext::number<ulong> m_idle_callback_identifier;
    ext::queue<std::jthread> m_current_threads;
    std::condition_variable m_condition_variable;
    std::mutex m_mutex;

    /* EVENT_TIMING */
    // TODO
};


#endif //SBROWSER2_WINDOW_HPP
