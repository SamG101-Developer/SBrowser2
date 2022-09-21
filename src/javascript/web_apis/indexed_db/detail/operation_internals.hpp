#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_OPERATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_OPERATION_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(indexed_db)

namespace indexed_db {class idb_cursor;}
namespace indexed_db {class idb_object_store;}


namespace indexed_db::detail::operation_internals
{
    auto store_record_into_object_store(
            idb_object_store* store,
            const record_t& record,
            ext::boolean_view no_overwrite_flag = false)
            -> void;

    auto retrieve_value_from_object_store(
            v8::Local<v8::Context> target_realm,
            idb_object_store* store,
            const key_range_t& range)
            -> ext::any;

    auto retrieve_multiple_values_from_object_store(
            v8::Local<v8::Context> target_realm,
            idb_object_store* store,
            const key_range_t& range,
            ext::number_view<ulonglong> count = 0)
            -> ext::vector<ext::any>;

    auto retrieve_key_from_object_store(
            idb_object_store* store,
            const key_range_t& range)
            -> ext::any;

    auto retrieve_multiple_keys_from_object_store(
            idb_object_store* store,
            const key_range_t& range,
            ext::number_view<ulonglong> count = 0)
            -> ext::vector<ext::any>;

    auto retrieve_referenced_value_from_index(
            v8::Local<v8::Context> target_realm,
            idb_object_store* store,
            const key_range_t& range)
            -> ext::any;

    auto retrieve_multiple_referenced_values_from_index(
            v8::Local<v8::Context> target_realm,
            idb_object_store* store,
            const key_range_t& range,
            ext::number_view<ulonglong> count = 0)
            -> ext::vector<ext::any>;

    auto retrieve_value_from_index(
            idb_object_store* store,
            const key_range_t& range)
            -> ext::any;

    auto retrieve_multiple_values_from_index(
            idb_object_store* store,
            const key_range_t& range,
            ext::number_view<ulonglong> count = 0)
            -> ext::vector<ext::any>;

    auto delete_records_from_object_store(
            idb_object_store* store,
            const key_range_t& range)
            -> void;

    auto count_records_in_range(
            idb_object_store* store,
            const key_range_t& range)
            -> ext::number<ulonglong>;

    auto clear_object_store(
            idb_object_store* store)
            -> void;

    auto iterate_cursor(
            v8::Local<v8::Context> target_realm,
            idb_cursor* cursor,
            ext::optional<record_t> key,
            ext::optional<record_t> primary_key,
            ext::number<ulonglong> count = 0)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_OPERATION_INTERNALS_HPP
