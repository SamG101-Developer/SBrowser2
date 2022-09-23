#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_DATABASE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_DATABASE_HPP

#include "dom/nodes/event_target.hpp"
namespace indexed_db {class idb_database;}

#include INCLUDE_INNER_TYPES(indexed_db)
namespace indexed_db {class idb_transaction;}
namespace indexed_db {class idb_object_store;}

class indexed_db::idb_database
        : public dom::nodes::event_target
{
public aliases:
    using enum detail::transaction_mode_t;

public constructors:
    idb_database();

public js_methods:
    auto transaction(ext::vector_view<ext::string> store_names, detail::transaction_mode_t mode = READONLY, ext::map<ext::string, ext::any>&& options = {}) -> idb_transaction;
    auto create_object_store(ext::string_view object_store_name, ext::map<ext::string, ext::any>&& options = {}) -> idb_object_store;
    auto close() -> void;
    auto delete_object_store(ext::string_view object_store_name) -> void;

private js_properties:
    ext::property<ext::string> name;
    ext::property<detail::database_version_t> version;
    ext::property<ext::vector<ext::string>> object_store_names;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<idb_transaction> m_upgrade_transaction;

private js_properties:
    auto get_object_store_names() const -> ext::vector<ext::string>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_IDB_DATABASE_HPP
