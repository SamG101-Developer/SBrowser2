#include "window.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"
#include "ext/threading.hpp"

#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "background_tasks/detail/processing_internals.hpp"

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/action/remove.hpp>


auto dom::nodes::window::request_idle_callback(
        background_tasks::detail::idle_request_callback_t&& callback,
        background_tasks::detail::idle_request_options_t&& options)
        -> ext::number<ulong>
{
    // Increase the callback identifier number, and add the callback into the class's list of callbacks. Get the current
    // handle as a variable.
    m_idle_callback_identifier += 1;
    m_idle_request_callbacks.emplace_back(std::move(callback));
    decltype(auto) handle = m_idle_callback_identifier;

    // Run the rest of the method in another thread (which is saved into a class list, so doesn't go out of scope), and
    // return the handle in the background
    go [this, options = std::move(options), &handle]
    {
        // Save the current thread into the list of threads in the class to keep it in scope once the method
        // ends.
        m_current_threads.push(this_thread);

        // Continue if the timeout value in the 'options' dictionary is greater than 0 (can't wait for <= 0
        // milliseconds)
        if (auto timeout = options.try_emplace("timeout", 0).first->second.to<ext::number<int>>(); timeout > 0)
        {
            // Sleep the thread for the correct number of milliseconds, and then wait for other instances of
            // this method to finish, as long as they started before this method did (their thread is before
            // them in the queue, so wait for this thread to be the first in the queue)
            std::this_thread::sleep_for(std::chrono::milliseconds(*timeout));

            // TODO

            // Queue a task on the idle task source so invoke the timeout algorithm for the 'handle', with
            // 'this' Window as an argument
            dom::detail::queue_task(
                    html::detail::idle_task_source,
                    BIND_FRONT(background_tasks::detail::invoke_idle_callback_timeout_algorithm, handle, this));
        }

        // This thread has finished executing, so remove it from the class's queue of saved threads
        // TODO
    };

    // Return the handle
    return handle;
}


auto dom::nodes::window::cancel_idle_task(
        ext::number<ulong> handle)
        -> void
{
    // Remove the callback at the 'handle' index from both the idle-request and runnable-idle callback lists.
    m_idle_request_callbacks  |= ranges::actions::remove_at_index(handle);
    m_runnable_idle_callbacks |= ranges::actions::remove_at_index(handle);
}
