#include "window_client.hpp"
#include "window_client_private.hpp"

#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/document_internals.hpp"
#include "html/detail/focus_internals.hpp"
#include "html/detail/task_internals.hpp"


auto service_workers::clients::window_client::focus()
        -> ext::promise<window_client*>
{
    // TODO : how to know what triggered the algorithm (user-interaction etc)
    ACCESS_PIMPL(window_client);

    auto e = js::env::env::surrounding(this);
    decltype(auto) service_worker_event_loop = e.js.agent();
    auto promise = ext::promise<window_client*>{};

    dom::detail::queue_task(
            html::detail::user_interaction_task_source,
            [this, d, service_worker_event_loop, &promise]
            {
        html::detail::focusing_steps(*d->browsing_context);

        decltype(auto) active_document = html::detail::active_document(d->browsing_context);
        auto e = js::env::env::relevant(active_document);

        auto frame_type = detail::get_frame_type(d->browsing_context);
        auto visibility_state = active_document->d_func()->visibiltiy_state;
        auto focus_state = html::detail::has_focus_steps(active_document);
        auto ancestor_origins_list = e.cpp.global<dom::nodes::window*>()->d_func()->location->d_func()->ancestor_origins_list;

        dom::detail::queue_task(
                html::detail::dom_manipulation_task_source,
                [d, frame_type, visibility_state, focus_state, &promise, ancestor_origins_list = std::move(ancestor_origins_list)]
                {
            JS_REALM_GET_RELEVANT(window_client);
            decltype(auto) window_client = detail::create_window_client(d->service_worker_client.get(), frame_type, visibility_state, focus_state, ancestor_origins_list);
            window_client->d_func()->docus_atte ? promise.resolve(window_client) : promise.reject(v8::Exception::TypeError(v8pp::to_v8(window_client_relevant_agent, u"")));
                },
                service_worker_event_loop);
            },
            nullptr /* TODO */);
}


auto service_workers::clients::window_client::get_visibility_state() const -> page_visibility::detail::visibility_state_t
{
    ACCESS_PIMPL(const window_client);
    return d->visibility_state;
}


auto service_workers::clients::window_client::get_focused() const -> ext::boolean
{
    ACCESS_PIMPL(const window_client);
    return d->focus_state;
}


auto service_workers::clients::window_client::get_ancestor_origins() const -> ext::vector_span<ext::string>
{
    ACCESS_PIMPL(const window_client);
    return {d->ancestor_origins_array.begin(), d->ancestor_origins_array.end()};
}
