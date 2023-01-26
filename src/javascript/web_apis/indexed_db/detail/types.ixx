module;
#include "ext/macros.hpp"
#include <swl/variant.hpp>


export module apis.indexed_db.types;
import apis.dom.types;
import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE(indexed_db)
{
    class idb_request;
    class idb_open_request;
    class idb_factory;
    class idb_database;
    class idb_object_store;
    class idb_index;
    class idb_key_range;
    class idb_cursor;
    class idb_transaction;
    class idb_version_change_event;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(indexed_db)
{
    // [2.1.0] - Database
    struct database_t;
    using name_t = ext::string;
    using version_t = ext::number<int>;

    // [2.1.1] - Database connection
    struct connection_t;

    // [2.2.2] - Object stores
    struct object_store_t;
    struct key_generator_t;
    using record_t = ext::pair<ext::any, ext::any>;

    // [2.2.3] - Object store handle
    struct object_store_handle_t;

    // [2.4]
    using key_t = ext::any;

    // [2.5]
    using key_path_t = ext::vector<ext::string>;

    // [2.6]
    struct index_t;
    struct index_handle_t;

    // [2.7] - Transactions
    enum class transaction_mode_t {READONLY, READWRITE, VERSIONCHANGE};
    enum class transaction_durability_hint_t {STRICT, RELAXED, DEFAULT};
    enum class transaction_state_t {ACTIVE, INACTIVE, COMMITTING, FINISHED};
    struct transaction_t;
    struct upgrade_transaction_t;

    // [2.8] - Requests
    struct request_t;
    struct open_request_t;
    using connection_queue_t = ext::queue<open_request_t*>;

    // [2.9] - Key ranges
    struct key_range_t;

    // [2.10] - Cursor
    enum class cursor_direction_t {NEXT, NEXTUNIQUE, PREV, PREVUNIQUE};
    struct cursor_t;
    using source_t = ext::variant<index_t*, object_store_t*, cursor_t*>;

    // [2.11] - Key generator
    struct key_generator_t;

    // [3]
    enum class idb_request_ready_state_t {PENDING, DONE};
}


struct indexed_db::detail::database_t
{
    name_t name;
    version_t version;
    ext::vector<std::unique_ptr<object_store_t>> object_stores;
    std::observer_ptr<upgrade_transaction_t> upgrade_transaction;
};


struct indexed_db::detail::connection_t // TODO : Connection.[[GetTheParent]]() {return Null;}
{
    version_t version;
    ext::boolean close_pending_flag = false;
    ext::vector<std::unique_ptr<object_store_t>> object_stores;
};


struct indexed_db::detail::object_store_t
{
    name_t name;
    key_path_t key_path;
    ext::vector<record_t> records;

    std::unique_ptr<key_generator_t> key_generator;

    auto uses_inline_keys() {return !key_path.empty();}
    auto uses_outline_keys() {return key_path.empty();}
};


struct indexed_db::detail::object_store_handle_t
{
    name_t name;
    std::observer_ptr<object_store_t> object_store;
    std::unique_ptr<transaction_t> transaction;
    ext::set<std::unique_ptr<index_t>> index_set;
};


struct indexed_db::detail::index_t
{
    std::observer_ptr<object_store_t> reference_object_store;
    ext::vector<record_t> records;
    ext::boolean unique_flag;
    ext::boolean multi_entry_flag;
};


struct indexed_db::detail::index_handle_t
{
    name_t name;
    std::observer_ptr<index_t> index;
    std::observer_ptr<object_store_handle_t> object_store_handle;
    std::unique_ptr<transaction_t> transaction;
};


struct indexed_db::detail::transaction_t // TODO : Transaction.[[GetTheParent]]() {return connection;}
{
    ext::vector<object_store_t*> scope;
    transaction_mode_t transaction_mode;
    transaction_durability_hint_t durability_hint;
    transaction_state_t state = transaction_state_t::ACTIVE;

    v8::Isolate* cleanup_event_loop;
    ext::vector<request_t*> request_list;
    ext::boolean error;

    auto has_overlapping_scope(const transaction_t& other) -> ext::boolean;
};


struct indexed_db::detail::upgrade_transaction_t : transaction_t
{
    transaction_mode_t transaction_mode = transaction_mode_t::VERSIONCHANGE;
};


struct indexed_db::detail::request_t // TODO : Request.[[GetTheParent]]() {return transaction;}
{
    ext::boolean processed_flag;
    ext::boolean done_flag;

    source_t* source;
    ext::any result;
    dom::dom_exception error;

    std::observer_ptr<transaction_t> transaction;
};


struct indexed_db::detail::open_request_t : request_t // TODO : OpenRequest.[[GetTheParent]]() {return Null;}
{};


struct indexed_db::detail::key_range_t
{
    key_t lower_bound;
    key_t upper_bound;

    ext::boolean lower_open_flag;
    ext::boolean upper_open_flag;
};


struct indexed_db::detail::cursor_t
{
    cursor_direction_t direction;
    ext::number<int> position;
    std::observer_ptr<ext::any> key;
    std::observer_ptr<ext::any> value;

    ext::boolean got_value_flag;
    ext::boolean key_only_flag;

    std::observer_ptr<request_t> request;
    std::observer_ptr<transaction_t> transaction;
    source_t source;

    auto effective_object_store() -> object_store_t*;
    auto effective_key() -> ext::any&;
};


struct indexed_db::detail::key_generator_t
{
    ext::number<long> current_position = 1; // TODO : Check this limits at 2**53
};
