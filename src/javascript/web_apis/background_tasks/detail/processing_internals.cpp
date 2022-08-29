#include "processing_internals.hpp"

#include "ext/optional.hpp"

#include "background_tasks/idle_deadline.hpp"

#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/window.hpp"

#include "high_resolution_time/performance.hpp"

#include "html/detail/task_internals.hpp"

#include <range/v3/algorithm/move_backward.hpp>
#include <range/v3/action/remove.hpp>


template <callable F>
auto background_tasks::detail::start_idle_period(
        dom::nodes::window* window,
        F&& get_deadline) -> void
{
    // If the ide period should be delayed, then return early from the method, so that the rest of the method can not
    // execute.
    return_if (should_idle_period_be_delayed());

    // Get the pending and run list, move all the items from the pending list into the run list, and clear the pending
    // list.
    decltype(auto) pending_list = window->m_idle_request_callbacks;
    decltype(auto) run_list = window->m_runnable_idle_callbacks;
    ranges::move_backward(pending_list, run_list.end());

    // Queue a task on the idle task source that 'invoke[s_the]_idle_callback_algorithm(...)' with the 'window' and
    // 'get_deadline' function.
    dom::detail::queue_task(html::detail::idle_task_source,
            [window, get_deadline = std::forward<F>(get_deadline)] mutable
            {invoke_idle_callbacks_algorithm(window, std::forward<F>(get_deadline));});
}


template <callable F>
auto background_tasks::detail::invoke_idle_callbacks_algorithm(
        dom::nodes::window* window,
        F&& get_deadline)
        -> high_resolution_time::detail::dom_high_res_time_stamp_t
{
    // If the ide period should end early, then return early from the method, so that the rest of the method can not
    // execute.
    return_if (should_idle_period_end_early()) 0.0;

    // Get the current time, and if it is before the deadline, and the window still has runnable callbacks, then
    // continue the method.
    auto now = high_resolution_time::performance{}.now();
    if (now < get_deadline() && !window->m_runnable_idle_callbacks.empty())
    {
        // Remove the first callback from the runnable callback list of the Window object.
        window->m_runnable_idle_callbacks.pop_front();

        // Create an IdleDeadline object using the 'get_deadline' function, and report any JavaScript exception throws
        // during construction.
        JS_EXCEPTION_HANDLER;
        idle_deadline deadline_arg {.m_get_deadline_time = std::forward<F>(get_deadline)};
        if (JS_EXCEPTION_HAS_THROWN) html::detail::report_exception(JS_EXCEPTION_MESSAGE);

        // If there is still a method in the Window's runnable callbacks list, then queue a task on the idle task source
        // to invoke the callbacks algorithm (move to next callback in Window's runnable callbacks list), with the same
        // 'get_deadline' method.
        if (!window->m_runnable_idle_callbacks.empty())
            dom::detail::queue_task(html::detail::idle_task_source,
                    [window, get_deadline = std::forward<F>(get_deadline)] mutable
                    {invoke_idle_callbacks_algorithm(window, std::forward<F>(get_deadline));});
    }
}


auto background_tasks::detail::invoke_idle_callback_timeout_algorithm(
        ext::number<ulong>&& handle,
        dom::nodes::window* window)
        -> void
{
    // The 'callback_candidate' is the callback in either the idle request callback list or runnable idle callback list
    // (whichever contains the index first), in the 'window' object. If neither list contains the index, then the
    // callback is empty / doesn't exist;
    idle_request_callback_t callback;
    if (window->m_idle_request_callbacks.size() < handle)
        callback = window->m_idle_request_callbacks.at(std::move(handle));
    else if (window->m_runnable_idle_callbacks.size() < handle)
        callback = window->m_runnable_idle_callbacks.at(std::move(handle));

    // Only continue if there is a callback (ext::function<Ts...> can hold 'empty' functions)
    if (!callback.empty())
    {
        // Remove the callback from both the lists in the 'window' -- the callback has been found in one list, but can
        // still exist in both lists. Get the current time as 'now'.
        window->m_idle_request_callbacks  |= ranges::actions::remove(callback);
        window->m_runnable_idle_callbacks |= ranges::actions::remove(callback);
        auto now = high_resolution_time::performance{}.now();

        // create an IdleDeadline object, assign the get deadline method to return the time 'now', and set the 'timeout'
        // attribute to true; as the deadline is 'now', it has already expired.
        idle_deadline deadline_arg;
        deadline_arg.m_get_deadline_time = [now = std::move(now)] {return now;};
        deadline_arg.m_timeout = true;

        // Call the callback with exception handling, and report any JavaScript exception throws during execution of the
        // algorithm.
        JS_EXCEPTION_HANDLER;
        callback(std::move(deadline_arg));
        if (JS_EXCEPTION_HAS_THROWN) html::detail::report_exception(JS_EXCEPTION_MESSAGE);
    }
}
