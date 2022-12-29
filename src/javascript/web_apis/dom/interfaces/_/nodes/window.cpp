module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/macros.hpp"
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/action/remove.hpp>


module apis.dom.window;
import apis.dom.window_private;

import ext.core;


auto dom::window::request_idle_callback(
        background_tasks::detail::idle_request_callback_t&& callback,
        idle_request_options_t&& options)
        -> ext::number<ulong>
{
    ACCESS_PIMPL;

    // Increase the callback identifier number, and add the callback into the class's list of callbacks. Get the current
    // handle as a variable.
    d->idle_callback_identifier += 1;
    d->idle_request_callbacks.emplace_back(std::move(callback));
    decltype(auto) handle = m_idle_callback_identifier;

    // Run the rest of the method in another thread (which is saved into a class list, so doesn't go out of scope), and
    // return the handle in the background
    _GO [this, options = std::move(options), &handle]
    {
        // Save the current thread into the list of threads in the class to keep it in scope once the method
        // ends.
        m_current_threads.push(this_thread);

        // Continue if the timeout value in the 'options' dictionary is greater than 0 (can't wait for <= 0
        // milliseconds)
        if (auto timeout = options[u"timeout"].to<ext::number<int>>(); timeout > 0)
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


auto dom::window::cancel_idle_task(
        ext::number<ulong> handle)
        -> void
{
    ACCESS_PIMPL;

    // Remove the callback at the 'handle' index from both the idle-request and runnable-idle callback lists.
    d->idle_request_callbacks  |= ranges::actions::remove_at_index(handle);
    d->runnable_idle_callbacks |= ranges::actions::remove_at_index(handle);
}


auto dom::window::get_window() const -> window_proxy*
{
    auto e = js::env::env::relevant(this);
    return v8pp::from_v8<window_proxy*>(e.js.agent(), e.js.realm()->Global()->GetPrototype()); // TODO
}


auto dom::window::get_document() const -> document*
{
    ACCESS_PIMPL;
    return d->document.get();
}


auto dom::window::get_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->navigable ? d->navigable->target_name() : u"";
}


auto dom::window::get_location() const -> html::other::location*
{
    ACCESS_PIMPL;
    return d->location.get();
}


auto dom::window::get_history() const -> html::other::history*
{
    ACCESS_PIMPL;
    return d->document->d_func()->history.get();
}


auto dom::window::get_custom_elements() const -> html::other::custom_element_registry*
{
    ACCESS_PIMPL;
    return d->custom_elements.get();
}


auto dom::window::get_closed() const -> ext::boolean
{
    ACCESS_PIMPL;
    return !d->document->d_func()->browsing_context || d->navigable->is_closing;
}


auto dom::window::get_top() const -> window_proxy*
{
    ACCESS_PIMPL;
    return d->navigable
            ? html::detail::top_level_traversable(d->navigable.get())->active_window_proxy
            : nullptr;
}


auto dom::window::get_parent() const -> window_proxy*
{
    ACCESS_PIMPL;
    return d->navigable
            ? (d->navigable = d->navigable->parent.get())->active_window_proxy()
            : nullptr;
}


auto dom::window::set_name(ext::string new_name) -> ext::string
{
    ACCESS_PIMPL;
    return_if (!d->navigable) u"";
    return d->navigable->active_session_history->document_state->navigable_target_name = std::move(new_name);
}
