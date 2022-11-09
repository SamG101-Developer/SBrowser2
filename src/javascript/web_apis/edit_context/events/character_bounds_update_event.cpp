#include "character_bounds_update_event.hpp"


edit_context::events::character_bounds_update_event::character_bounds_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(character_bounds_update_event);

    ACCESS_PIMPL(character_bounds_update_event);
    d->range_start = event_init[u"rangeStart"].to<decltype(d->range_start)>();
    d->range_end = event_init[u"rangeEnd"].to<decltype(d->range_end)>();
}
