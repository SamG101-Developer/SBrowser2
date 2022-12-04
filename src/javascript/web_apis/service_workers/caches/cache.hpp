#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_HPP

#include "dom_object.hpp"
namespace service_workers::caches {class cache;}
namespace service_workers::caches {class cache_private;}


#include "ext/optional.ixx"

#include "ext/span.hpp"
#include INCLUDE_INNER_TYPES(service_workers)
#include INCLUDE_INNER_TYPES(fetch)
namespace fetch {class request;}
namespace fetch {class response;}


class service_workers::caches::cache
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(cache);
    MAKE_PIMPL(cache);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto match(fetch::detail::request_info_t&& request, detail::cache_query_options_t&& options = {}) -> ext::promise<fetch::response*>;
    auto match_all(ext::optional<fetch::detail::request_info_t> request, detail::cache_query_options_t&& options = {}) -> ext::promise<ext::vector_span<fetch::response*>>;
    auto keys(fetch::detail::request_info_t&& request, detail::cache_query_options_t&& options = {}) -> ext::promise<ext::vector_span<fetch::request*>>;
    auto add(fetch::detail::request_info_t&& request) -> ext::promise<void>;
    auto add_all(ext::vector<fetch::detail::request_info_t>&& requests) -> ext::promise<void>;
    auto put(fetch::detail::request_info_t&& request, fetch::response* response) -> ext::promise<void>;
    auto delete_(fetch::detail::request_info_t&& request, detail::cache_query_options_t options = {}) -> ext::promise<ext::boolean>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_CACHES_CACHE_HPP
