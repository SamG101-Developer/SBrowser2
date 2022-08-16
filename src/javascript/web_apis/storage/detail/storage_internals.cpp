#include "storage_internals.hpp"

#include "ext/functional.hpp"
#include "ext/type_traits.hpp"

#include USE_INNER_TYPES(streams)

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/ref.hpp>

using namespace std::string_literals;


auto storage::detail::equal_storage_keys(
        const storage_key_t& key_a,
        const storage_key_t& key_b)
        -> ext::boolean
{
    // two storage keys are equal if their origins are equal, and because the keys are the origins, the keys are used as
    // the parameter to the 'same_origin(...)' check
    return html::detail::same_origin(key_a, key_b);
}


auto storage::detail::obtain_storage_key(
        v8::Local<v8::Object> environment)
        -> ext::optional<storage_key_t>
{
    // get the key for non-storage purposes, and if the returned key (which is an origin) is an opaque origin, or the
    // use has disabled the storage from being usable to the browser, then return a failure
    auto key = obtain_storage_key_for_non_storage_purposes(environment);
    return_if (html::detail::is_opaque_origin(key)) ext::nullopt;
    return_if (false /* TODO : storage disabled */) ext::nullopt;

    return key;
}


auto storage::detail::obtain_storage_key_for_non_storage_purposes(
        v8::Local<v8::Object> environment)
        -> ext::optional<storage_key_t>
{
    // TODO
}


auto storage::detail::obtain_storage_shelf(
        storage_shed_t& storage_shed,
        v8::Local<v8::Object> environment,
        storage_type_t type)
        -> ext::optional<storage_shelf_t>
{
    // get the storage key for the environment, and if the origin is a failure, then return a failure for the storage
    // shelf, because the key has to be used with the shed to determine the shelf
    auto key = obtain_storage_key(environment);
    return_if(!key.has_value()) ext::nullopt;

    // the storage shed's shelf (associated with the key) either already exists, or is the result of creating a new
    // storage shelf for the 'type', and whichever of these values is present is what is returned (existing or new
    // shelf)
    storage_shed.try_emplace(*key, create_storage_shelf(type));
    return storage_shed.at(*key);
}


auto storage::detail::obtain_local_storage_shelf(
        v8::Local<v8::Object> environment)
        -> ext::optional<storage_shelf_t>
{
    // the local storage shelf is the storage self for the environment and 'local_storage_shed', with the type LOCAL
    // (this is just a convenience function with contextual meaning)
    return obtain_storage_shelf(local_storage_shed, environment, storage_type_t::LOCAL);
}


auto storage::detail::obtain_storage_bottle_map(
        storage_type_t type,
        v8::Local<v8::Object> environment,
        const storage_identifier_t& identifier)
        -> ext::optional<storage_bottle_t::proxy_map_t>
{
    // determine the correct 'session_shed' depending on the 'type' (either local or session). the local storage shed is
    // stored as a variable because it is renewed for each session, where-as the local storage shed is obtained from the
    // environment
    auto storage_shed = type == storage_type_t::LOCAL ? local_storage_shed : storage_shed_t{};
    // TODO : get session_shed

    // obtain the storage shelf for the 'storage_shed', and return a failure if the 'storage_shelf' obtained is a
    // failure
    auto storage_shelf = obtain_storage_shelf(storage_shed, environment, type);
    return_if (!storage_shelf.has_value()) ext::nullopt;

    // determine the 'storage_bucket' -> 'storage_bottle', and create a proxy map whose backend map is the
    // 'storage_bottle's map. add the proxy map to the 'storage_bottle's proxy maps
    auto storage_bucket = storage_shelf->bucket_map.at("default");
    auto storage_bottle = storage_bucket.bottle_map.at("identifier");
    auto proxy_map = storage_bottle_t::proxy_map_t{.map=storage_bottle.map};
    storage_bottle.proxy_maps.insert(proxy_map);

    // return the proxy map (this method is to get the bottle map, not the bottle)
    return proxy_map;
}


auto storage::detail::obtain_local_storage_bottle_map(
        v8::Local<v8::Object> environment,
        const storage_identifier_t& identifier)
        -> ext::optional<storage_bottle_t::proxy_map_t>
{
    // convenience method to obtain the local storage bottle map (fixed LOCAL first parameter)
    return obtain_storage_bottle_map(storage_type_t::LOCAL, environment, identifier);
}


auto storage::detail::obtain_session_storage_bottle_map(
        v8::Local<v8::Object> environment,
        const storage_identifier_t& identifier)
        -> ext::optional<storage_bottle_t::proxy_map_t>
{
    // convenience method to obtain the local storage bottle map (fixed SESSION first parameter)
    return obtain_storage_bottle_map(storage_type_t::SESSION, environment, identifier);
}


auto storage::detail::create_storage_shelf(
        storage_type_t type)
        -> storage_shelf_t
{
    // create a new storage shelf with a "default" bucket, which is a newly created bucket
    storage_shelf_t storage_shelf;
    storage_shelf.bucket_map.emplace("default", create_storage_bucket(type));
}


auto storage::detail::create_storage_bucket(
        storage_type_t type)
        -> storage_bucket_t
{
    // create a new bucket, and insert all the registered endpoints whose types contain the 'type'
    storage_bucket_t storage_bucket;
    for (const storage_endpoint_t& storage_endpoint: registered_storage_endpoints) // | ranges::views::filter(ext::bind_back(ranges::contains, std::move(type))))
        storage_bucket.bottle_map.emplace(storage_endpoint.identifier, storage_bottle_t{.quota = storage_endpoint.quota});
    return storage_bucket;
}
