#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE__TYPEDEFS_HPP

#include INCLUDE_INNER_TYPES(html)


namespace storage::detail
{
    struct storage_endpoint_t;
    struct storage_shelf_t;
    struct storage_bucket_t;
    struct local_storage_bucket_t;
    struct session_storage_bucket_t;
    struct storage_bottle_t;

    enum class storage_type_t {LOCAL, SESSION};
    enum class storage_bucket_mode_t {BEST_EFFORT, PERSISTENT};

    using storage_identifier_t = ext::u8string;
    using storage_key_t = ext::tuple<html::detail::origin_t*>;
    using storage_shed_t = ext::map<storage_key_t, storage_shelf_t*>;
    using bucket_map_t = ext::map<ext::string, std::unique_ptr<storage_bucket_t>>;
    using bottle_map_t = ext::map<storage_identifier_t, std::unique_ptr<storage_bottle_t>>;
    using storage_map_t = ext::map<ext::string, ext::any>;
    using quota_t = ext::optional<ext::number<int>>;

    using storage_estimate_t = ext::map<ext::string, ext::number<ulonglong>>;
}

// namespace storage::detail
// {
//     enum class storage_type_t {LOCAL, SESSION};
//     enum class storage_bucket_mode_t {BEST_EFFORT, PERSISTENT};
//
//     using storage_identifier_t = ext::string;
//     using storage_key_t = ext::string; // TODO -> struct?
//
//     struct storage_endpoint_t
//     {
//         storage_identifier_t identifier;
//         ext::set<storage_type_t> storage_types;
//         ext::number<int> quota;
//     };
//
//     struct storage_bottle_t
//     {
//         using map_t = ext::map<ext::string, ext::any>;
//         struct proxy_map_t {map_t map; auto operator->() const {return map;}};
//
//         map_t map;
//         ext::set<proxy_map_t> proxy_maps;
//         ext::number<int> quota;
//     };
//
//     struct storage_bucket_t
//     {
//         ext::map<storage_identifier_t, storage_bottle_t> bottle_map;
//         storage_bucket_mode_t mode;
//     };
//
//     using bucket_map_t = ext::map<ext::string, storage_bucket_t>;
//
//     struct storage_shelf_t
//     {
//         bucket_map_t bucket_map;
//         ext::number<ulonglong> storage_usage;
//         ext::number<ulonglong> storage_quota;
//     };
//
//     using storage_shed_t = ext::map<storage_key_t, storage_shelf_t>;
//
//     storage_shed_t local_storage_shed;
//     storage_key_t local_storage;
//     storage_key_t session_storage;
//
//     ext::vector<storage_endpoint_t> registered_storage_endpoints
//     {
//         storage_endpoint_t {.identifier="caches", .storage_types = {storage_type_t::LOCAL}, .quota = 0},
//         storage_endpoint_t {.identifier="indexedDB", .storage_types = {storage_type_t::LOCAL}, .quota = 0},
//         storage_endpoint_t {.identifier="localStorage", .storage_types = {storage_type_t::LOCAL}, .quota = std::pow(5, 20)},
//         storage_endpoint_t {.identifier="serviceWorkerRegistrations", .storage_types = {storage_type_t::LOCAL}, .quota = 0},
//         storage_endpoint_t {.identifier="sessionStorage", .storage_types = {storage_type_t::SESSION}, .quota = std::pow(5, 20)},
//     };
// }


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE__TYPEDEFS_HPP
