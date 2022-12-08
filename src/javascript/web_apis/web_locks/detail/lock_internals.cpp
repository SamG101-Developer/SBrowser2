#include "lock_internals.hpp"











#include "html/detail/task_internals.hpp"

#include "web_locks/_typedefs.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"

#include <range/v3/view/for_each.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/action/remove.hpp>


web_locks::detail::lock_t::lock_t()
{
    auto e = js::env::env::relevant(this);

    auto lock_release = [this, &e]
    {
        release_lock(this);
        web_idl::detail::resolve_promise(released_promise, e.js.realm(), waiting_promise);
    };

    web_idl::detail::upon_settlement(
            waiting_promise, e.js.realm(),
            BIND_FRONT(dom::detail::queue_task, html::detail::web_locks_task_source, std::move(lock_release)));
}


auto web_locks::detail::request_lock(
        ext::promise<ext::any>& promise,
        v8::Isolate* agent,
        ext::string&& client_id,
        const web_locks::detail::lock_manager_t& manager,
        web_locks::detail::lock_granted_callback_t&& callback,
        resource_name_t&& name,
        web_locks::detail::lock_mode_t mode,
        ext::boolean if_availablle,
        ext::boolean steal,
        dom::abort::abort_signal* signal)
        -> std::unique_ptr<lock_request_t>
{
    auto request = std::make_unique<lock_request_t>();
    request->agent = agent;
    request->client_id = std::move(client_id);
    request->manager = &manager;
    request->name = std::move(name);
    request->mode = mode;
    request->callback = std::move(callback);
    request->promise = promise;
    request->signal = signal;

    if (signal)
        signal->d_func()->abort_algorithms.emplace_back(BIND_FRONT(signal_to_abort_request, *request, signal));

    dom::detail::queue_task(html::detail::web_locks_task_source,
            [steal, manager, request = request.get()]
            {
        decltype(auto) queue = manager.lock_request_queue_map.at(request->name); // TODO : []
        if (steal)
        {
            using enum dom::detail::dom_exception_error_t;
            using enum ranges::filter_compare_t;
            manager.held_lock_set // TODO : Optimize
                    | ranges::views::transform(ext::underlying)
                    | ranges::views::filter_eq<EQ>(&lock_t::name, request->name, ext::identity)
                    | ranges::views::for_each(BIND_BACK(web_idl::detail::reject_promise, dom::other::dom_exception{u8"", ABORT_ERR}, &lock_t::released_promise))
                    | ranges::views::for_each([&manager](lock_t& lock) {manager.held_lock_set |= ranges::actions::remove(lock);});
            // TODO : Prepend something
        }

        else
        {
            // TODO
        }

        process_lock_request_queue(queue);
            });
}


auto web_locks::detail::release_lock(web_locks::detail::lock_t& lock) -> void
{
    ASSERT(&std::this_thread::get_id == html::detail::web_locks_task_source.id.get());
    lock.manager->held_lock_set |= ranges::actions::transform(ext::deref) | ranges::actions::remove(lock);
    process_lock_request_queue(lock.manager->lock_request_queue_map[lock.name]);
}


auto web_locks::detail::process_lock_request_queue(web_locks::detail::lock_request_queue_t& queue) -> void
{
    ASSERT(&std::this_thread::get_id == html::detail::web_locks_task_source.id.get());

    for (decltype(auto) request: queue | ranges::views::transform(ext::underlying))
    {
        return_if (!grantable(*request));
        queue |= ranges::actions::transform(ext::underlying) | ranges::actions::remove(request);

        auto lock = std::make_unique<lock_t>();
        lock->agent = request->agent;
        lock->manager = request->manager.get();
        lock->client_id = request->client_id;
        lock->name = request->name;
        lock->mode = request->mode;
        lock->released_promise = request->promise;
        lock->waiting_promise = web_idl::detail::create_promise<void>(request->agent->GetCurrentContext());

        request->manager->held_lock_set.emplace(std::move(lock));

        // TODO : Enqueue steps somewhere
    }
}
