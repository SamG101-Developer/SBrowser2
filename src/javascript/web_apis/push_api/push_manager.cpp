#include "push_manager.hpp"
#include "push_manager_private.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/task_internals.hpp"

#include "ext/boolean.hpp"


auto push_api::push_manager::subscribe(
        detail::push_subscription_options_init_t&& options)
        -> ext::promise<push_subscription*>
{
    auto promise = ext::promise<push_subscription*>{};
    using enum dom::detail::dom_exception_error_t;

    GO [&promise, options = std::move(options)] mutable
    {
        if (!options[u8"userVisibleOnly"].to<ext::boolean>() /* TODO : and UA requires it to be True */)
            dom::detail::queue_task(html::detail::networking_task_source,
                    [&promise]
                    {promise.reject(dom::other::dom_exception{"TODO", NOT_ALLOWED_ERR});});
    };

    return promise;
}
