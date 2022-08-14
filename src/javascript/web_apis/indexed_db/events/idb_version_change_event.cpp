#include "idb_version_change_event.hpp"


indexed_db::events::idb_version_change_event::idb_version_change_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
        , old_version{event_init.try_emplace("oldVersion", 0).first->second.to<ext::number<ulonglong>>()}
        , new_version{event_init.try_emplace("oldVersion"   ).first->second.to<ext::number<ulonglong>>()}
{}
