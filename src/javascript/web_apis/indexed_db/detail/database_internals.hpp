#ifndef SBROWSER2_DATABASE_INTERNALS_HPP
#define SBROWSER2_DATABASE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/queue.hpp"
#include "ext/set.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"

#include "indexed_db/_typedefs.hpp"
#include <range/v3/view/any_view.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/map.hpp>
#include <v8-forward.h>

#include "dom/nodes/event_target.hpp"
#include "dom/other/dom_exception.hpp"

namespace indexed_db::detail::database_internals
{
    struct record_t;
    struct key_generator_t;
    struct database_t;

    struct object_store_t;
    struct object_store_handle_t;
    struct index_t;
    struct index_handle_t;

    struct connection_t;
    struct transaction_t;
    struct request_t;
    struct open_request_t;

    struct key_range_t;
    struct cursor_t;

    using source_t = ext::variant<std::reference_wrapper<object_store_t>, std::reference_wrapper<index_t>>;

    template <typename T>
    concept source_like_c = requires
    {
        requires type_is<T, object_store_t, index_t>;
        {T::records} -> std::same_as<ext::vector<record_t*>&>;
    };

    auto compare_two_keys(
            const record_t& a,
            const record_t& b)
            -> ext::number<int>;

    auto is_key_path_valid(
            ext::vector_view<ext::string> key_path)
            -> ext::boolean;

    auto uses_in_line_keys(
            const object_store_t& object_store)
            -> ext::boolean;

    auto uses_out_of_line_keys(
            const object_store_t& object_store)
            -> ext::boolean;

    auto transactions_have_overlapping_scope(
            const transaction_t& transaction_a,
            const transaction_t& transaction_b)
            -> ext::boolean;

    auto cleanup_index_database_transactions()
            -> void;

    auto key_range_containing_only(
            const key_range_t& key_range,
            const record_t& key)
            -> ext::boolean;

    auto key_in_key_range(
            const key_range_t& key_range,
            const record_t& key)
            -> ext::boolean;

    auto unbounded_key_range(
            const key_range_t& key_range)
            -> ext::boolean;

    auto convert_value_to_key_range(
            ext::any_view value,
            ext::boolean_view null_disallowed_flag = false)
            -> key_range_t;

    auto generate_key_for_object_store(
            object_store_t& object_store)
            -> ext::number<long>;

    auto possible_update_key_generator(
            object_store_t& object_store
            const record_t& record)
            -> void;

    ext::queue<open_request_t*> connection_queue;
}


/**
 * a record contains a key (variant type), and an associated value which is ext::any, and cast to the correct type by
 * using the key-casting. they are stored in an object store
 */
struct indexed_db::detail::database_internals::record_t
{
public constructors:
    ~record_t();

public cpp_operators:
    auto operator==(const record_t& other) const {return compare_two_keys(*this, other) == 0;};
    auto operator<=>(const record_t& other) const -> int {return compare_two_keys(*this, other);};

public cpp_properties:
    any_key_t key;
    ext::any value;
};


/**
 *
 */
struct indexed_db::detail::database_internals::key_generator_t
{
public cpp_properties:
    ext::number<long> current_number = 1;
};


/**
 * an object store contains a list of records
 */
struct indexed_db::detail::database_internals::object_store_t
{
public cpp_properties:
    ext::string name;
    ext::vector<record_t> records;
    ext::vector<ext::string> key_path;

public cpp_static_methods:
    static auto derive_key(const key_generator_t& generator);
    static auto derive_key(const record_t& record);
    static auto derive_key(ext::string_view key_path);

private cpp_properties:
    key_generator_t m_generator;
};


/**
 * an object store handle contains an object store and a transaction
 */
struct indexed_db::detail::database_internals::object_store_handle_t
{
public friends:
    friend struct index_t;
    friend struct index_handle_t;

public constructors:
    object_store_handle_t(
            const object_store_t& object_store,
            const transaction_t& transaction)
            : name(object_store.name)
            , index_set(object_store.records | ranges::views::enumerate | ranges::views::keys | ranges::to<ext::vector<ext::number<int>>>)
            , m_object_store(object_store)
            , m_transaction(transaction)
    {}

public cpp_properties:
    ext::string name;
    ext::vector<ext::number<int>> index_set;

private cpp_properties:
    const object_store_t& m_object_store;
    const transaction_t& m_transaction;
};


/**
 * an index contains a object store handle
 */
struct indexed_db::detail::database_internals::index_t
{
public friends:
    friend struct index_handle_t;

public constructors:
    explicit index_t(
            const object_store_handle_t& object_store)
            : records(object_store.m_object_store.records)
            , m_object_store(object_store)
    {}

public cpp_properties:
    ext::string name;
    ext::boolean unique_flag;
    ext::boolean multi_entry_flag;
    const ext::vector<record_t>& records;

private cpp_properties:
    const object_store_handle_t& m_object_store;
};


/**
 *
 */
struct indexed_db::detail::database_internals::index_handle_t
{
public constructors:
    explicit index_handle_t(
            const index_t& index)
            : name(index.name)
            , m_index(index)
            , m_object_store_handle(index.m_object_store)
            , m_transaction(index.m_object_store.m_transaction)
    {}

public cpp_properties:
    ext::string name;

private cpp_properties:
    const index_t& m_index;
    const object_store_handle_t& m_object_store_handle;
    const transaction_t& m_transaction;
};


/**
 *
 */
struct indexed_db::detail::database_internals::connection_t
        : protected dom::nodes::event_target
{
public constructors:
    ~connection_t() {close_pending_flag = true;}

public cpp_properties:
    ext::number<int> version;
    ext::boolean close_pending_flag;
    ext::set<object_store_t> object_store_set;

protected cpp_methods:
    auto get_the_parent(dom::events::event* event) -> event_target* override {return nullptr;}
};


/**
 *
 */
struct indexed_db::detail::database_internals::transaction_t
        : protected dom::nodes::event_target
{
public constructors:
    explicit transaction_t(
            const connection_t& connection)
            : m_connection(connection)
    {}

    ext::set<object_store_t> scope;
    transaction_mode_t mode;
    transaction_state_t state = transaction_state_t::ACTIVE;
    durability_hint_t durability_t;

public cpp_properties:
    v8::Isolate* event_loop = nullptr;
    ext::vector<request_t*> request_list;
    dom::other::dom_exception error;

protected cpp_methods:
    auto get_the_parent(dom::events::event* event) -> event_target* override {return &m_connection;}

private cpp_properties:
    const connection_t& m_connection;
};


/**
 *
 */
struct indexed_db::detail::database_internals::request_t
        : protected dom::nodes::event_target
{
public cpp_properties:
    ext::boolean processed_flag;
    ext::boolean done_flag = false;
    void* source;

    ext::string result;
    dom::other::dom_exception error;

protected cpp_methods:
    auto get_the_parent(dom::events::event* event) -> event_target* override {return &m_transaction;}

private cpp_properties:
    const transaction_t m_transaction;
};


/**
 *
 */
struct indexed_db::detail::database_internals::open_request_t
        : public request_t
{
protected cpp_methods:
    auto get_the_parent(dom::events::event* event) -> event_target* override {return nullptr;}
};


/**
 *
 */
struct indexed_db::detail::database_internals::key_range_t
{
    std::unique_ptr<record_t> lower_bound;
    std::unique_ptr<record_t> upper_bound;
    ext::boolean lower_open_flag;
    ext::boolean upper_open_flag;
};


/**
 *
 */
struct indexed_db::detail::database_internals::cursor_t
{
public constructors:
    cursor_t(
            const request_t& request,
            const transaction_t& transaction,
            const source_like_c auto& source)
            : records(source->records)
            , m_request(request)
            , m_transaction(transaction)
            , m_source(source)
    {}

public cpp_properties:
    const ext::vector<record_t>& records;
    cursor_direction_t direction;
    ext::vector<record_t>::iterator position;
    ext::vector<record_t>::iterator object_store_position;
    record_t current_record;

    ext::boolean got_value_flag;
    ext::boolean key_value_flag;

private cpp_properties:
    const request_t& m_request;
    const transaction_t& m_transaction;
    source_t m_source;
};

#endif //SBROWSER2_DATABASE_INTERNALS_HPP
