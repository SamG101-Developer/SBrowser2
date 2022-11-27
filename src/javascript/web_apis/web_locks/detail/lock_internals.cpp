#include "lock_internals.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "web_locks/_typedefs.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"


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
