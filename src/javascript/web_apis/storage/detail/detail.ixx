module;
#include "ext/macros.hpp"
#include <tl/expected.hpp>


export module apis.storage.detail;
import apis.storage.types;

import js.env.realms;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(storage)
{
    // [4.2] - Storage Keys
    auto obtain_storage_key(js::env::env& environment) -> ext::expected<storage_key_t>;
    auto obtain_storage_key_for_non_storage_purposes(js::env::env& environment) -> storage_key_t;
    auto equal_storage_keys(const storage_key_t& key_a, const storage_key_t& key_b) -> ext::boolean;

    // [4.3] - Storage Sheds
    // [4.4] - Storage Shelves
    auto obtain_storage_shelf(storage_shed_t& storage_shed, js::env::env& environment, storage_type_t type) -> ext::expected<storage_shelf_t*>;
    auto obtain_local_storage_shelf(js::env::env& environment) -> ext::expected<storage_shelf_t*>;
    auto create_storage_shelf(storage_type_t type) -> std::unique_ptr<storage_shelf_t>;

    // [4.5] - Storage Buckets
    auto create_storage_bucket(storage_type_t type) -> std::unique_ptr<storage_bucket_t>;

    // [4.6] - Storage Bottles
    auto obtain_storage_bottle_map(storage_type_t type, js::env::env& environment, ext::view_of_t<storage_identifier_t> identifier) -> ext::expected<std::unique_ptr<storage_map_t>>;
    auto obtain_local_storage_bottle_map(js::env::env& environment, ext::view_of_t<storage_identifier_t> identifier) -> ext::expected<std::unique_ptr<storage_map_t>>;
    auto obtain_session_storage_bottle_map(js::env::env& environment, ext::view_of_t<storage_identifier_t> identifier) -> ext::expected<std::unique_ptr<storage_map_t>>;

    // [6] - Usage & Quota
    auto storage_usage(const storage_shelf_t& shelf) -> ext::number<ulonglong>;
    auto storage_quota(const storage_shelf_t& shelf) -> ext::number<ulonglong>;

    // Other
    const ext::vector<storage_endpoint_t> registered_storage_endpoints =
    {
            storage_endpoint_t{u8"caches", {storage_type_t::LOCAL}, ext::nullopt},
            storage_endpoint_t{u8"indexedDB", {storage_type_t::LOCAL}, ext::nullopt},
            storage_endpoint_t{u8"localStorage", {storage_type_t::LOCAL}, 5 * ext::pow(2, 20)},
            storage_endpoint_t{u8"serviceWorkerRegistration", {storage_type_t::LOCAL}, ext::nullopt},
            storage_endpoint_t{u8"sessionStorage", {storage_type_t::SESSION}, 5 * ext::pow(2, 20)}
    };
};
