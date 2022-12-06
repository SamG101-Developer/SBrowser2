#include "lock_manager.hpp"
#include "html/detail/task_internals.hpp"
#include "lock_manager_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"


#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"
#include "dom/other/dom_exception.hpp"

#include "html

#include "web_idl/detail/type_mapping_internals.hpp"
#include "web_locks/_typedefs.hpp"


auto web_locks::lock_manager::request(
        ext::string_view name,
        detail::lock_granted_callback_t&& callback,
        detail::lock_options_t&& options)
        -> ext::promise<ext::any>
{
    using enum dom::detail::dom_exception_error_t;
    auto e = js::env::env::relevant(this);

    // TODO : Document check (multiple possible environments though - Window & Worker)

    decltype(auto) manager = detail::obtain_lock_manager(e);

    if (!manager.has_value())
        return web_idl::detail::create_rejected_promise<ext::any>(dom::other::dom_exception{u8"", SECURITY_ERR}, e.js.realm());

    if (name.starts_with(0x002d))
        return web_idl::detail::create_rejected_promise<ext::any>(dom::other::dom_exception{u8"", NOT_SUPPORTED_ERR}, e.js.realm());

    if (options[u"steal"].to<ext::boolean>() && options[u"ifAvailable"].to<ext::boolean>())
        return web_idl::detail::create_rejected_promise<ext::any>(dom::other::dom_exception{u8"", NOT_SUPPORTED_ERR}, e.js.realm());

    if (options[u"steal"].to<ext::boolean>() && options[u"mode"] != detail::lock_mode_t::EXCLUSIVE)
        return web_idl::detail::create_rejected_promise<ext::any>(dom::other::dom_exception{u8"", NOT_SUPPORTED_ERR}, e.js.realm());

    if (options[u"signal"].to<dom::abort::abort_signal*>() && (options[u"steal"].to<ext::boolean>() || options[u"ifAvailable"].to<ext::boolean>()))
        return web_idl::detail::create_rejected_promise<ext::any>(dom::other::dom_exception{u8"", NOT_SUPPORTED_ERR}, e.js.realm());

    if (decltype(auto) signal = options[u"signal"].to<dom::abort::abort_signal*>(); signal->d_func()->aborted())
        return web_idl::detail::create_rejected_promise<ext::any>(signal.d_func()->abort_reason.to<dom::other::dom_exception>(), e.js.realm());

    auto promise = web_idl::detail::create_promise<ext::any>(e.js.realm());
    detail::request_lock(
            promise, v8::Isolate::GetCurrent(), e.cpp.settings()->id, std::move(manager), std::move(callback), name,
            options[u"mode"].to<detail::lock_mode_t>(),
            options[u"ifAvailable"].to<ext::boolean>(),
            options[u"steal"].to<ext::boolean>(),
            options[u"signal"].to<dom::abort::abort_signal*>());

    return promise;
}


auto web_locks::lock_manager::query() -> ext::promise<detail::lock_manager_snapshot_t>
{
    using enum dom::detail::dom_exception_error_t;
    auto e = js::env::env::relevant(this);

    decltype(auto) manager = detail::obtain_lock_manager(e);

    if (dom::detail::is_document_fully_active(e.cpp.global<dom::nodes::window*>()->d_func()->document.get()))
        return web_idl::detail::create_rejected_promise<detail::lock_manager_snapshot_t>(dom::other::dom_exception{u8"", INVALID_STATE_ERR}, e.js.realm());

    if (!manager.has_value())
        return web_idl::detail::create_rejected_promise<detail::lock_manager_snapshot_t>(dom::other::dom_exception{u8"", SECURITY_ERR}, e.js.realm());

    auto promise = web_idl::detail::create_promise<detail::lock_manager_snapshot_t>(e.js.realm());
    dom::detail::queue_task(html::detail::web_locks_task_source, [&manager, &promise] {detail::snapshot_lock_state(manager, promise);});
    return promise;
}
