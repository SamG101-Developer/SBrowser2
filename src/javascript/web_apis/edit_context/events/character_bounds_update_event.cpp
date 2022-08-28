#include "character_bounds_update_event.hpp"


edit_context::events::character_bounds_update_event::character_bounds_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, range_start)
        , SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(event_init, range_end)
{}
