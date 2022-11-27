#include "lock_manager.hpp"
#include "lock_manager_private.hpp"


auto web_locks::lock_manager::request(
        ext::string_view name,
        detail::lock_granted_callback_t&& callback,
        detail::lock_options_t&& options)
        -> ext::promise<ext::any>
{
    auto e = js::env::env::relevant(this);

    // TODO : Document check (multiple possible environments though - Window & Worker)

    if (detail::obtain_lock_manager())
}
