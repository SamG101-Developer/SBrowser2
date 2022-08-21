#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_HPP

#include "dom_object.hpp"
namespace service_workers::caches {class cache;}

#include <future>
#include USE_INNER_TYPES(service_workers)
#include USE_INNER_TYPES(fetch)
namespace fetch {class response;}

class service_workers::caches::cache
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(cache);
    cache() = default;

public js_methods:
    auto match(fetch::detail::request_info_t request, detail::cache_query_options_t&& options = {}) -> std::promise<fetch::response*>;
    auto match_all(fetch::detail::request_info_t = nullptr, detail::cache_query_options_t&& options = {}) -> std::promise<const ext::vector<fetch::response*>>;
    auto keys(fetch::detail::request_info_t = nullptr, detail::cache_query_options_t&& options = {}) -> std::promise<const ext::vector<fetch::request*>>;
    auto add(fetch::detail::request_info_t request) -> std::promise<void>;
    auto add_all(ext::vector<fetch::detail::request_info_t>& requests) -> std::promise<void>;
    auto put(fetch::detail::request_info_t request, fetch::response* response) -> std::promise<void>;
    auto delete_(fetch::detail::request_info_t request, detail::cache_query_options_t options = {}) -> std::promise<ext::boolean>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_HPP
