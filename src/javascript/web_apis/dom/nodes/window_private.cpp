module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/errors.hpp"


module apis.dom.window_private;

import ext.concepts;
import ext.number;


template <ext::callable F>
auto dom::window_private::start_idle_period(F&& get_deadline) -> hr_time::dom_high_res_time_stamp
{
    // If the ide period should be delayed, then return early from the method, so that the rest of the method can not
    // execute.
    return_if (should_idle_period_be_delayed());

    // Get the pending and run list, move all the items from the pending list into the run list, and clear the pending
    // list.
    decltype(auto) pending_list = window->d_func()->idle_request_callbacks;
    decltype(auto) run_list = window->d_func()->runnable_idle_callbacks;
    ranges::move_backward(pending_list, run_list.end());

    // Queue a task on the idle task source that 'invoke[s_the]_idle_callback_algorithm(...)' with the 'window' and
    // 'get_deadline' function.
    dom::detail::queue_task(html::detail::idle_task_source,
            [window, get_deadline = std::forward<F>(get_deadline)] mutable
            {invoke_idle_callbacks_algorithm(window, std::forward<F>(get_deadline));});
}


template <ext::callable F>
auto dom::window_private::invoke_idle_callbacks_algorithm(F&& get_deadline) -> hr_time::dom_high_res_time_stamp
{
    // If the ide period should end early, then return early from the method, so that the rest of the method can not
    // execute.
    return_if (should_idle_period_end_early()) 0.0;

    // Get the current time, and if it is before the deadline, and the window still has runnable callbacks, then
    // continue the method.
    auto e = js::env::env::current();
    auto global_object = v8pp::to_v8(e.js.agent(), window);
    auto now = hr_time::detail::current_hr_time(global_object);

    if (now < get_deadline() && !window->d_func()->runnable_idle_callbacks.empty())
    {
        // Remove the first callback from the runnable callback list of the Window object.
        window->d_func()->runnable_idle_callbacks.pop_front();

        // Create an IdleDeadline object using the 'get_deadline' function, and report any JavaScript exception throws
        // during construction.
        JS_EXCEPTION_HANDLER;
        idle_deadline deadline_arg {.m_get_deadline_time = std::forward<F>(get_deadline)};
        if (JS_EXCEPTION_HAS_THROWN) html::detail::report_exception(JS_EXCEPTION_MESSAGE);

        // If there is still a method in the Window's runnable callbacks list, then queue a task on the idle task source
        // to invoke the callbacks algorithm (move to next callback in Window's runnable callbacks list), with the same
        // 'get_deadline' method.
        if (!window->d_func()->runnable_idle_callbacks.empty())
            dom::detail::queue_task(html::detail::idle_task_source,
                    [window, get_deadline = std::forward<F>(get_deadline)] mutable
                    {invoke_idle_callbacks_algorithm(window, std::forward<F>(get_deadline));});
    }
}


auto dom::window_private::invoke_idle_callback_timeout(ext::number<ulong> handle) -> void // TODO
{
    // The 'callback_candidate' is the callback in either the idle request callback list or runnable idle callback list
    // (whichever contains the index first), in the 'window' object. If neither list contains the index, then the
    // callback is empty / doesn't exist;
    idle_request_callback_t callback;
    if (window->d_func()->idle_request_callbacks.size() < handle)
        callback = window->d_func()->idle_request_callbacks.at(handle);
    else if (window->d_func()->runnable_idle_callbacks.size() < handle)
        callback = window->d_func()->runnable_idle_callbacks.at(handle);

    // Only continue if there is a callback (ext::function<Ts...> can hold 'empty' functions)
    if (!callback.empty())
    {
        // Remove the callback from both the lists in the 'window' -- the callback has been found in one list, but can
        // still exist in both lists. Get the current time as 'now'.
        window->d_func()->idle_request_callbacks  |= ranges::actions::remove(callback);
        window->d_func()->runnable_idle_callbacks |= ranges::actions::remove(callback);

        auto e = js::env::env::current();
        auto global_object = v8pp::to_v8(e.js.agent(), window);
        auto now = hr_time::detail::current_hr_time(global_object);

        // create an IdleDeadline object, assign the get deadline method to return the time 'now', and set the 'timeout'
        // attribute to true; as the deadline is 'now', it has already expired.
        idle_deadline deadline_arg;
        deadline_arg->d_func()->get_deadline_time = [now] {return now;};
        deadline_arg->d_func()->timeout = true;

        // Call the callback with exception handling, and report any JavaScript exception throws during execution of the
        // algorithm.
        JS_EXCEPTION_HANDLER;
        callback(std::move(deadline_arg));
        if (JS_EXCEPTION_HAS_THROWN) html::detail::report_exception(JS_EXCEPTION_MESSAGE);
    }
}

