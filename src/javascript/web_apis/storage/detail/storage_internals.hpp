#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_DETAIL_STORAGE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_DETAIL_STORAGE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/set.hpp"
#include USE_INNER_TYPES(streams)

#include <v8-forward.h>

namespace storage::detail
{
    auto equal_storage_keys(
            const storage_key_t& key_a,
            const storage_key_t& key_b)
            -> ext::boolean;

    auto obtain_storage_key(
            v8::Local<v8::Object> environment)
            -> ext::optional<storage_key_t>;

    auto obtain_storage_key_for_non_storage_purposes(
            v8::Local<v8::Object> environment)
            -> ext::optional<storage_key_t>;

    auto obtain_storage_shelf(
            storage_shed_t& storage_shed,
            v8::Local<v8::Object> environment,
            storage_type_t type)
            -> ext::optional<storage_shelf_t>;

    auto obtain_local_storage_shelf(
            v8::Local<v8::Object> environment)
            -> ext::optional<storage_shelf_t>;

    auto obtain_storage_bottle_map(
            storage_type_t type,
            v8::Local<v8::Object> environment,
            const storage_identifier_t& identifier)
            -> ext::optional<storage_bottle_t::proxy_map_t>;

    auto obtain_local_storage_bottle_map(
            v8::Local<v8::Object> environment,
            const storage_identifier_t& identifier)
            -> ext::optional<storage_bottle_t::proxy_map_t>;

    auto obtain_session_storage_bottle_map(
            v8::Local<v8::Object> environment,
            const storage_identifier_t& identifier)
            -> ext::optional<storage_bottle_t::proxy_map_t>;

    auto create_storage_shelf(
            storage_type_t type)
            -> storage_shelf_t;

    auto create_storage_bucket(
            storage_type_t type)
            -> storage_bucket_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_DETAIL_STORAGE_INTERNALS_HPP
