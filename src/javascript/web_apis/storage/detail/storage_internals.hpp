#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_DETAIL_STORAGE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_DETAIL_STORAGE_INTERNALS_HPP

#include "ext/boolean.ixx"
#include "ext/expected.ixx"
#include "ext/number.ixx"
#include "ext/optional.hpp"
#include "ext/set.hpp"
#include INCLUDE_INNER_TYPES(storage)
#include INCLUDE_INNER_TYPES(streams)

#include <v8-forward.h>
namespace js::env {class env;}


namespace storage::detail
{
    auto equal_storage_keys(
            const storage_key_t& key_a,
            const storage_key_t& key_b)
            -> ext::boolean;

    auto obtain_storage_key(
            js::env::env& environment)
            -> ext::expected<storage_key_t>;

    auto obtain_storage_key_for_non_storage_purposes(
            js::env::env& environment)
            -> storage_key_t;

    auto obtain_storage_shelf(
            storage_shed_t& storage_shed,
            js::env::env& environment,
            storage_type_t type)
            -> ext::expected<storage_shelf_t*>;

    auto obtain_local_storage_shelf(
            js::env::env& environment)
            -> ext::expected<storage_shelf_t*>;

    auto obtain_storage_bottle_map(
            storage_type_t type,
            js::env::env& environment,
            ext::string_view identifier)
            -> ext::expected<std::unique_ptr<storage_map_t>>;

    auto obtain_local_storage_bottle_map(
            js::env::env& environment,
            ext::string_view identifier)
            -> ext::expected<std::unique_ptr<storage_map_t>>;

    auto obtain_session_storage_bottle_map(
            js::env::env& environment,
            ext::string_view identifier)
            -> ext::expected<std::unique_ptr<storage_map_t>>;

    auto create_storage_shelf(
            storage_type_t type)
            -> std::unique_ptr<storage_shelf_t>;

    auto create_storage_bucket(
            storage_type_t type)
            -> std::unique_ptr<storage_bucket_t>;

    auto storage_usage(
            storage_shelf_t& shelf)
            -> ext::number<size_t>;

    auto storage_quota(
            storage_shelf_t& shelf)
            -> ext::number<size_t>;
};


struct storage::detail::storage_endpoint_t
{
    storage_identifier_t identifier;
    ext::set<storage_type_t> types;
    quota_t quota;
};


struct storage::detail::storage_shelf_t
{
    bucket_map_t bucket_map;
};


struct storage::detail::storage_bucket_t
{
    bottle_map_t bottle_map;
    virtual ~storage_bucket_t();
};


struct storage::detail::local_storage_bucket_t : storage_bucket_t
{
    storage_bucket_mode_t mode = storage_bucket_mode_t::BEST_EFFORT;
};


struct storage::detail::session_storage_bucket_t : storage_bucket_t
{};


struct storage::detail::storage_bottle_t
{
    storage_map_t map; // TODO : K, V?
    ext::set<storage_map_t*> proxy_map_reference_set;
    quota_t quota;
};


namespace storage::detail
{
    const auto registered_storage_endpoints = ext::set<storage_endpoint_t>
            {
        storage_endpoint_t{.identifier = u8"caches", .types = {storage_type_t::LOCAL}, .quota = ext::nullopt},
        storage_endpoint_t{.identifier = u8"indexedDB", .types = {storage_type_t::LOCAL}, .quota = ext::nullopt},
        storage_endpoint_t{.identifier = u8"localStorage", .types = {storage_type_t::LOCAL}, .quota = 5 * std::pow(2, 20)},
        storage_endpoint_t{.identifier = u8"serviceWorkerRegistrations", .types = {storage_type_t::LOCAL}, .quota = ext::nullopt},
        storage_endpoint_t{.identifier = u8"sessionStorage", .types = {storage_type_t::SESSION}, .quota = 5 * std::pow(2, 20)},
            };
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_DETAIL_STORAGE_INTERNALS_HPP
