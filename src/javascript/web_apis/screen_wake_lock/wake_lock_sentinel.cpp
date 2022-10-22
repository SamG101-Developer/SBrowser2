#include "wake_lock_sentinel.hpp"
#include "wake_lock_sentinel_private.hpp"


screen_wake_lock::wake_lock_sentinel::wake_lock_sentinel()
{
    INIT_PIMPL(wake_lock_sentinel);

    HTML_CONSTRUCTOR;
}


auto screen_wake_lock::wake_lock_sentinel::get_released() const -> ext::boolean
{
    ACCESS_PIMPL(const wake_lock_sentinel);
    return d->released;
}


auto screen_wake_lock::wake_lock_sentinel::get_type() const -> detail::wake_lock_type
{
    ACCESS_PIMPL(const wake_lock_sentinel);
    return d->type;
}
