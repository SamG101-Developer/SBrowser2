module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


export module apis.storage.types;

import apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(storage)
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


struct storage::detail::storage_endpoint_t
{
    storage_identifier_t identifier;
    ext::set<storage_type_t> types;
    ext::number<int> quota;
};


struct storage::detail::storage_bucket_t
{
    bottle_map_t bottle_map;
};


struct storage::detail::local_storage_bucket_t : storage_bucket_t
{
    storage_bucket_mode_t mode;
    ext::map<bottle_map_t::key, std::unique_ptr<local_storage_bucket_t> bottle_map;
};


struct storage::detail::session_storage_bucket_t : storage_bucket_t
{
    ext::map<bottle_map_t::key, std::unique_ptr<session_storage_bucket_t> bottle_map;
};
