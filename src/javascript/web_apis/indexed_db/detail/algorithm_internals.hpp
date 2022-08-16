#pragma once
#include "dom/other/dom_exception.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/optional.hpp"
#include "ext/variant.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(indexed_db)
#include USE_INNER_TYPES(storage)
namespace dom::other {class dom_exception;}
namespace indexed_db {class idb_request;}
namespace indexed_db {class idb_transaction;}

namespace indexed_db::detail::algorithm_internals
{
    auto open_database(
            const storage::detail::storage_key_t& storage_key,
            const database_name_t& name,
            const database_version_t& version,
            idb_request* request)
            -> ext::variant<connection_t, dom::other::dom_exception>;

    auto close_database(
            const connection_t& connection,
            ext::boolean_view forced_flag)
            -> void;

    auto delete_database(
            const storage::detail::storage_key_t& storage_key,
            const database_name_t& name,
            idb_request* request)
            -> ext::variant<database_version_t, dom::other::dom_exception>;

    auto commit_transaction(
            idb_transaction* transaction)
            -> void;

    auto abort_transaction(
            idb_transaction* transaction,
            dom::other::dom_exception& error)
            -> void;

    auto asynchronously_execute_request(
            const source_like_c auto& source,
            idb_request* request = nullptr)
            -> void;

    auto run_upgrade_transaction(
            const connection_t& connection,
            const database_version_t& version,
            idb_request* request)
            -> void;

    auto abort_upgrade_transaction(
            idb_transaction* transaction)
            -> void;

    auto fire_success_event(
            idb_request* request)
            -> void;

    auto fire_error_event(
            idb_request* request)
            -> void;

    auto clone(
            v8::Local<v8::Object> value,
            v8::Local<v8::Context> realm,
            idb_transaction* transaction)
            -> v8::Local<v8::Object>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_ALGORITHM_INTERNALS_HPP
