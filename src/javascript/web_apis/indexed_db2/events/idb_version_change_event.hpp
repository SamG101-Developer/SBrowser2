#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_EVENTS_IDB_VERSION_CHANGE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_EVENTS_IDB_VERSION_CHANGE_EVENT_HPP


namespace indexed_db::events {class idb_version_change_event;}

class indexed_db::events::idb_version_change_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(idb_version_change_event);
    idb_version_change_event() = default;
    idb_version_change_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_properties:
    ext::property<ext::number<ulonglong>> old_version;
    ext::property<ext::number<ulonglong>> new_version;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_EVENTS_IDB_VERSION_CHANGE_EVENT_HPP
