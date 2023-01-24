module;
#include "ext/macros.hpp"


export module apis.indexed_db.detail;
import ext.core;
import apis.indexed_db.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(indexed_db)
{
    auto create_sorted_name_list(ext::span<name_t> names) -> ext::vector<name_t>;
    auto compare_two_keys(const ext::any& a, const ext::any& b) -> ext::number<int>;
    auto cleanup_indexed_database_transactions(const transaction_t&) -> ext::boolean;

    auto key_lt(const ext::any& a, const ext::any& b) -> ext::boolean;
    auto key_gt(const ext::any& a, const ext::any& b) -> ext::boolean;
    auto key_eq(const ext::any& a, const ext::any& b) -> ext::boolean;

    auto contains_key(const key_range_t& key_range, const key_t& key) -> ext::boolean;
    auto contains_only_key(const key_range_t& key_range, const key_t& key) -> ext::boolean;
    auto is_unbounded_key_range(const key_range_t& key_range) -> ext::boolean;
    template <typename T> auto convert_value_to_keyrange(T&& value, ext::boolean null_disallowed_flag = false) -> std::unique_ptr<key_range_t>;

    auto generate_key(object_store_t* store) -> key_t;
    auto possibly_update_key_generator(obejct_store_t* store, const key_t& key) -> void;
}
