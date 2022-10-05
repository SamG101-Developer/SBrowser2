#include "extendable_event.hpp"
#include "extendable_event_private.hpp"

#include "service_workers/detail/event_internals.hpp"


auto service_workers::events::extendable_event::wait_until(
        ext::promise<ext::any>&& f)
        -> void
{
    detail::add_lifetime_promise(std::move(f), this);
}
