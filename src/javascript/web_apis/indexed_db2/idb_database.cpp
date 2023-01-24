#include "idb_database.hpp"


indexed_db::idb_database::idb_database()
{
    bind_get(object_store_names);
}


auto indexed_db::idb_database::create_object_store(
        ext::string_view object_store_name,
        ext::map<ext::string, ext::any>&& options)
        -> idb_object_store
{}
