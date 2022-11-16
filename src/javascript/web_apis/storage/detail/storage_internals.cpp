#include "storage_internals.hpp"

#include "ext/expected.hpp"
#include "ext/functional.hpp"
#include "ext/hashing.hpp"
#include "ext/type_traits.hpp"

#include "javascript/environment/realms.hpp"

#include "html/detail/origin_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/filter.hpp>


auto storage::detail::equal_storage_keys(
        const storage_key_t& key_a,
        const storage_key_t& key_b)
        -> ext::boolean
{
    // Two storage keys are equal if their origins are equal, and because the keys are the origins, the keys are used as
    // the parameter to the 'same_origin(...)' check.
    using namespace ext::literals;
    return html::detail::same_origin(*key_a[0_tag], *key_b[0_tag]);
}


auto storage::detail::obtain_storage_key(
        js::env::env& environment)
        -> ext::expected<storage_key_t>
{
    // Get the key for non-storage purposes, and if the returned key (which is an origin) is an opaque origin, or the
    // use has disabled the storage from being usable to the browser, then return a failure.
    using namespace ext::literals;
    auto key = obtain_storage_key_for_non_storage_purposes(environment);
    return_if (html::detail::is_opaque_origin(*key[0_tag])) ext::failure;
    return_if (false /* TODO : storage disabled */) ext::failure;

    return key;
}


auto storage::detail::obtain_storage_key_for_non_storage_purposes(
        js::env::env& environment)
        -> storage_key_t
{
    decltype(auto) origin = environment.cpp.settings()->origin.get();
    return ext::make_tuple(origin);
}


auto storage::detail::obtain_storage_shelf(
        storage_shed_t& storage_shed,
        js::env::env& environment,
        storage_type_t type)
        -> ext::expected<storage_shelf_t*>
{
    // Get the storage key for the environment, and if the origin is a failure, then return a failure for the storage
    // shelf, because the key has to be used with the shed to determine the shelf.
    auto key = obtain_storage_key(environment);
    return_if (!key.has_value()) ext::failure;

    // The storage shed's shelf (associated with the key) either already exists, or is the result of creating a new
    // storage shelf for the 'type', and whichever of these values is present is what is returned (existing or new
    // shelf).
    storage_shed.try_emplace(*key, create_storage_shelf(type));
    return storage_shed[*key];
}


auto storage::detail::obtain_local_storage_shelf(
        js::env::env& environment)
        -> ext::expected<storage_shelf_t*>
{
    // the local storage shelf is the storage self for the environment and 'local_storage_shed', with the type LOCAL
    // (this is just a convenience function with contextual meaning)
    return obtain_storage_shelf(*environment.cpp.settings()->local_storage, environment, storage_type_t::LOCAL);
}


auto storage::detail::obtain_storage_bottle_map(
        storage::detail::storage_type_t type,
        js::env::env& environment,
        ext::string_view identifier)
        -> ext::expected<std::unique_ptr<storage_map_t>>
{
    // determine the correct 'session_shed' depending on the 'type' (either local or session). the local storage shed is
    // stored as a variable because it is renewed for each session, where-as the local storage shed is obtained from the
    // environment
    auto storage_shed = type == storage_type_t::LOCAL
            ? *environment.cpp.settings()->local_storage
            : *environment.cpp.settings()->session_storage;

    // obtain the storage shelf for the 'storage_shed', and return a failure if the 'storage_shelf' obtained is a
    // failure
    auto storage_shelf = obtain_storage_shelf(storage_shed, environment, type);
    return_if (!storage_shelf.has_value()) ext::failure;

    // determine the 'storage_bucket' -> 'storage_bottle', and create a proxy map whose backend map is the
    // 'storage_bottle's map. add the proxy map to the 'storage_bottle's proxy maps
    auto storage_bucket = *storage_shelf.value()->bucket_map[u"default"];
    auto storage_bottle = *storage_bucket.bottle_map[u8"identifier"];
    auto proxy_map = std::make_unique<storage_map_t>();
    proxy_map.reset(&storage_bottle.map);
    storage_bottle.proxy_map_reference_set.emplace(proxy_map);

    // return the proxy map (this method is to get the bottle map, not the bottle)
    return proxy_map;
}


auto storage::detail::obtain_local_storage_bottle_map(
        js::env::env& environment,
        ext::string_view identifier)
        -> ext::expected<std::unique_ptr<storage_map_t>>
{
    // convenience method to obtain the local storage bottle map (fixed LOCAL first parameter)
    return obtain_storage_bottle_map(storage_type_t::LOCAL, environment, identifier);
}


auto storage::detail::obtain_session_storage_bottle_map(
        js::env::env& environment,
        ext::string_view identifier)
        -> ext::expected<std::unique_ptr<storage_map_t>>
{
    // convenience method to obtain the local storage bottle map (fixed SESSION first parameter)
    return obtain_storage_bottle_map(storage_type_t::SESSION, environment, identifier);
}


auto storage::detail::create_storage_shelf(
        storage::detail::storage_type_t type)
        -> std::unique_ptr<storage_shelf_t>
{
    // create a new storage shelf with a "default" bucket, which is a newly created bucket
    auto storage_shelf = std::make_unique<storage_shelf_t>();
    storage_shelf->bucket_map.emplace(u"default", create_storage_bucket(type));
    return storage_shelf;
}


auto storage::detail::create_storage_bucket(
        storage::detail::storage_type_t type)
        -> std::unique_ptr<storage_bucket_t>
{
    // create a new bucket, and insert all the registered endpoints whose types contain the 'type'
    std::unique_ptr<storage_bucket_t> storage_bucket = type == storage_type_t::LOCAL
            ? std::make_unique<local_storage_bucket_t>()
            : std::make_unique<session_storage_bucket_t>();

    using enum ranges::filter_compare_t;
    for (decltype(auto) endpoint: registered_storage_endpoints | ranges::views::filter(BIND_BACK(ranges::contains, type), &storage_endpoint_t::types))
    {
        storage_bucket->bottle_map[endpoint.identifier] = std::make_unique<storage_bottle_t>();
        storage_bucket->bottle_map[endpoint.identifier]->quota = endpoint.quota;
    }

    return storage_bucket;
}
