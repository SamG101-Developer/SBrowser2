#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CACHE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CACHE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(service_workers)


namespace service_workers::detail
{
    auto query_cache(
            const fetch::detail::request_t& request,
            cache_query_options_t&& options = {},
            request_response_list_t&& request_response_list = {})
            -> request_response_list_t&;

    auto request_matches_cached_item(
            const fetch::detail::request_t& request_query,
            const fetch::detail::request_t& request,
            ext:optional<const fetch::detail::response_t&> response = ext::nullopt,
            cache_query_options_t&& options = {})
            -> ext::boolean;

    auto batch_cache_operations(
            const ext::vector<cache_batch_operation_t>& operations)
            -> request_response_list_t&;
}


struct service_workers::detail::cache_batch_operation_t
{
    cache_batch_operation_type_t type;
    fetch::detail::request_t& request;
    fetch::detail::response_t& response;
    detail::cache_query_options_t options;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CACHE_INTERNALS_HPP
