#ifndef SBROWSER2_DATABASE_INTERNALS_HPP
#define SBROWSER2_DATABASE_INTERNALS_HPP



#include "ext/queue.ixx"
#include "ext/set.hpp"
#include "ext/type_traits.ixx"
#include "ext/vector.hpp"

#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(indexed_db)
#include INCLUDE_INNER_TYPES(storage)

namespace indexed_db {class idb_open_request;}
namespace indexed_db {class idb_transaction;}

namespace indexed_db::detail::database_internals
{
    auto compare_two_keys(
            const record_t& a,
            const record_t& b)
            -> ext::number<short>;

    auto is_key_path_valid(
            const key_path_t& key_path)
            -> ext::boolean;

    auto uses_in_line_keys(
            indexed_db::idb_object_store* object_store)
            -> ext::boolean;

    auto uses_out_of_line_keys(
            indexed_db::idb_object_store* object_store)
            -> ext::boolean;

    auto transactions_have_overlapping_scope(
            indexed_db::idb_transaction* transaction_a,
            indexed_db::idb_transaction* transaction_b)
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
            idb_object_store* object_store)
            -> ext::number<long>;

    auto possible_update_key_generator(
            idb_object_store* object_store,
            const record_t& record)
            -> void;

    ext::queue<idb_open_request*> connection_queue;
}


#endif //SBROWSER2_DATABASE_INTERNALS_HPP
