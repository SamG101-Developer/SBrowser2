#include "idb_version_change_event.hpp"


indexed_db::events::idb_version_change_event::idb_version_change_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
        , SET_PROPERTY_FROM_OPTIONS(event_init, old_version, 0)
        , SET_PROPERTY_FROM_OPTIONS(event_init, new_version, 0)
{}
