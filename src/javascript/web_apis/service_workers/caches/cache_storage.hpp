#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_STORAGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_STORAGE_HPP

#include "dom_object.hpp"
namespace service_workers::caches {class cache_storage;}

#include "ext/promise.hpp"
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(service_workers)
namespace service_workers::clients {class client;}
namespace fetch {class request;}
namespace fetch {class response;}

class service_workers::caches::cache_storage
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(cache_storage);
    cache_storage() = default;

public js_methods:
    auto match(
            fetch::detail::request_info_t request,
            detail::multi_cache_query_options_t&& options = {})
            -> ext::promise<fetch::response*>;

    auto has(
            ext::string_view cache_name)
            -> ext::promise<ext::boolean>;

    auto open(
            ext::string_view cache_name)
            -> ext::promise<caches::cache>;

    auto delete_(
            ext::string_view cache_name)
            -> ext::promise<ext::boolean>;

    auto keys()
            -> ext::promise<ext::vector<ext::string>>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_STORAGE_HPP
